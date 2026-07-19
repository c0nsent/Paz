#include "pomodoro-stats.hpp"
#include "core/constants.hpp"

#include <QGuiApplication>


namespace impl
{
    PomodoroStatsEntry::PomodoroStatsEntry() : PomodoroStatsEntry{QDate::currentDate()} {}

    PomodoroStatsEntry::PomodoroStatsEntry(const QDate date) : m_date{date}, m_pomodoros{0}, m_totalTime{0, 0} {}


    PomodoroStatsEntry::PomodoroStatsEntry(const QDate date, const u16 pomodoros, const QTime totalTime)
        : m_date{date}
        , m_pomodoros{pomodoros}
        , m_totalTime{totalTime}
    {
    }

    
    auto PomodoroStatsEntry::date() const noexcept -> QDate { return m_date; }
    
    auto PomodoroStatsEntry::pomodoros() const noexcept -> u16 { return m_pomodoros; }
    
    auto PomodoroStatsEntry::totalTime() const noexcept -> QTime  { return m_totalTime; }
    
    
    void PomodoroStatsEntry::addPomodoro(const QTime duration)
    {
        m_pomodoros++;
        m_totalTime = m_totalTime.addMSecs(duration.msecsSinceStartOfDay());
    }


    auto PomodoroStatsEntry::operator==(const PomodoroStatsEntry& rhs) const noexcept -> bool { return m_date == rhs.m_date; }

    auto PomodoroStatsEntry::operator==(const QDate otherDate) const noexcept -> bool { return this->m_date == otherDate; }


    PomodoroStats::PomodoroStats(QObject *parent)
        : QObject{parent}
        , m_settings{QGuiApplication::organizationDomain(), "Statistics"}
    {
        const auto entryCount{ m_settings.beginReadArray("Entries") };
        m_stats.reserve(entryCount);

        for (i32 i{0}; i != entryCount; i++)
        {
            m_settings.setArrayIndex(i);
            m_stats.emplace_back(
                m_settings.value("date").toDate(),
                m_settings.value("pomodoros").toUInt(),
                m_settings.value("totalTime").toTime()
            );
        }

        m_settings.endArray();
    }


    auto PomodoroStats::contains(const QDate date) const noexcept -> bool { return m_stats.contains(date); }


    auto PomodoroStats::get(const QDate date) const -> PomodoroStatsEntry
    {
        if (not contains(date)) return {};



        return m_stats[m_stats.indexOf(date)];
    }

    auto PomodoroStats::get(QDate begin, const QDate end) const -> QList<PomodoroStatsEntry>
    {
        QList<PomodoroStatsEntry> result;
        const auto size{begin.daysTo(end)};

        if (size <= 0) return result;

        result.reserve(size);

        //Если гарантировать хронологическое расположение объектов, то можно будет упростить эту хуйню

        for (; begin < end; begin = begin.addDays(1))
        {
            PomodoroStatsEntry entry{ contains(begin) ? m_stats[m_stats.indexOf(begin)] : PomodoroStatsEntry{} };
            result.emplace_back(entry);
        }

        return result;
    }

    auto PomodoroStats::size() const noexcept -> qsizetype { return m_stats.size(); }


    void PomodoroStats::addPomodoro(const QTime pomodoroDuration)
    {
        addPomodoro(QDate::currentDate(), pomodoroDuration );
    }


    void PomodoroStats::addPomodoro(const QDate date, const QTime pomodoroDuration)
    {
        if (not contains(date))
        {
            m_stats.emplaceBack(date, 1, pomodoroDuration);
            emit newEntryAdded(date);

            m_settings.beginWriteArray("statistics");
            m_settings.setArrayIndex(static_cast<i32>(m_stats.size()));
            m_settings.setValue("date", date);
            m_settings.setValue("pomodoros", 1);
            m_settings.setValue("totalTime",pomodoroDuration);
            m_settings.endArray();
            return;
        }

        auto &entry{ m_stats[m_stats.indexOf(date)] };

        entry.addPomodoro(pomodoroDuration);

        const i32 settingsIndex{std::invoke([&]
        {
            const auto size{m_settings.beginReadArray("statistics")};
            for (i32 i{0}; i != size; i++)
            {
                m_settings.setArrayIndex(i);
                if (m_settings.value("date").toDate() == date)
                {
                    m_settings.endArray();
                    return i;
                };
            }
            m_settings.endArray();

            return -1;
        })};


        m_settings.beginWriteArray("statistics");
        m_settings.setArrayIndex(settingsIndex);
        m_settings.setValue("pomodoros", entry.pomodoros());
        m_settings.setValue("totalTime", entry.totalTime());
        m_settings.endArray();

        emit entryChanged(date);
    }


    void PomodoroStats::removeEntry(const QDate date)
    {
        m_stats.remove(m_stats.indexOf(date));
        emit entryRemoved(date);
    }


    void PomodoroStats::sync() { m_settings.sync(); }
}
