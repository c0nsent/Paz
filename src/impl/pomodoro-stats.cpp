#include "pomodoro-stats.hpp"
#include "core/constants.hpp"

#include <QGuiApplication>


namespace impl
{
    PomodoroStatsEntry::PomodoroStatsEntry(const QDate date, const u16 pomodoros, const std::chrono::seconds totalTime) 
        : m_date{date}
        , m_pomodoros{pomodoros}
        , m_totalTime{totalTime}
    {
    }
    
    
    PomodoroStatsEntry::PomodoroStatsEntry(const QDate date, const u16 pomodoros, const i64 totalTimeInSeconds) 
        : m_date{date}
        , m_pomodoros{pomodoros}
        , m_totalTime{std::chrono::seconds{totalTimeInSeconds}}
    {
    }
    
    
    auto PomodoroStatsEntry::date() const noexcept -> QDate { return m_date; }
    
    auto PomodoroStatsEntry::pomodoros() const noexcept -> u16 { return m_pomodoros; }
    
    auto PomodoroStatsEntry::totalTime() const noexcept -> i64 { return m_totalTime.count(); }
    
    
    void PomodoroStatsEntry::addPomodoro(const std::chrono::seconds duration)
    {
        m_pomodoros++;
        m_totalTime += duration;
    }
    
    
    void PomodoroStatsEntry::addPomodoro(const i64 duration) { addPomodoro(std::chrono::seconds{duration}); }

    auto PomodoroStatsEntry::operator==(const PomodoroStatsEntry& rhs) const noexcept -> bool { return m_date == rhs.m_date; }

    auto PomodoroStatsEntry::operator==(const QDate otherDate) const noexcept -> bool { return this->m_date == otherDate; }


    PomodoroStats::PomodoroStats(QObject *parent)
        : QObject{parent}
        //, m_settings{QGuiApplication::organizationDomain(), "Statistics"}
        , m_stats{m_settings.beginReadArray("statistics")}
    {
        for (i32 i{0}; i != m_stats.size(); i++)
        {
            m_settings.setArrayIndex(i);
            m_stats.emplace_back(
                m_settings.value("date").toDate(),
                m_settings.value("pomodoros").toUInt(),
                std::chrono::seconds{m_settings.value("totalTime").toUInt()}
            );
        }

        m_settings.endArray();
    }


    auto PomodoroStats::contains(const QDate date) const noexcept -> bool { return m_stats.contains(date); }


    auto PomodoroStats::get(const QDate date) const noexcept -> PomodoroStatsEntry
    {
        if (not contains(date)) return {};

        return m_stats[m_stats.indexOf(date)];
    }

    auto PomodoroStats::get(QDate begin, const QDate end) const -> QList<PomodoroStatsEntry>
    {
        QList<PomodoroStatsEntry> result{begin.daysTo(end)};

        for (; begin < end; begin = begin.addDays(1))
        {
            PomodoroStatsEntry entry{ contains(begin) ? m_stats[m_stats.indexOf(begin)] : PomodoroStatsEntry{} };
            result.emplace_back(entry);
        }

        return result;
    }

    auto PomodoroStats::size() const -> qsizetype { return m_stats.size(); }


    void PomodoroStats::addPomodoro(const std::chrono::seconds pomodoroDuration)
    {
        addPomodoro(pomodoroDuration, QDate::currentDate());
    }


    void PomodoroStats::addPomodoro(std::chrono::seconds pomodoroDuration, const QDate date)
    {
        if (not contains(date))
        {
            m_stats.emplaceBack(date, 1, pomodoroDuration);
            emit newEntryAdded(date);

            m_settings.beginWriteArray("statistics");
            m_settings.setArrayIndex(static_cast<i32>(m_stats.size()));
            m_settings.setValue("date", date);
            m_settings.setValue("pomodoros", 1);
            m_settings.setValue("totalTime",static_cast<qint64>(pomodoroDuration.count()));
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
        m_settings.setValue("totalTime", static_cast<qint64>(entry.totalTime()));
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
