#include "pomodoro-stats.hpp"
#include "core/constants.hpp"

#include <QGuiApplication>

namespace impl
{
    bool PomodoroStats::DataEntry::operator==(const DataEntry& rhs) const noexcept { return date == rhs.date; }

    bool PomodoroStats::DataEntry::operator==(const QDate otherDate) const noexcept { return this->date == otherDate; }


    PomodoroStats::PomodoroStats(QObject *parent)
        : QObject{parent}
        , m_settings{QGuiApplication::organizationDomain(), "Statistics"}
    {
        const auto size{m_settings.beginReadArray("statistics")};
        m_stats.reserve(size);

        for (i32 i{0}; i != size; i++)
        {
            m_settings.setArrayIndex(i);
            m_stats.emplaceBack(
                m_settings.value("date").toDate(),
                m_settings.value("pomodoros").toUInt(),
                std::chrono::seconds{m_settings.value("totalTime").toUInt()}
            );
        }

        m_settings.endArray();
    }


    auto PomodoroStats::contains(const QDate date) const noexcept -> bool { return m_stats.contains(date); }

    auto PomodoroStats::get(const QDate date) const -> DataEntry
    {
        if (not contains(date)) return {};

        return m_stats[m_stats.indexOf(date)];
    }

    auto PomodoroStats::get(QDate begin, const QDate end) const -> QList<DataEntry>
    {
        QList<DataEntry> result{begin.daysTo(end)};

        for (; begin < end; begin = begin.addDays(1))
        {
            DataEntry entry{ contains(begin) ? m_stats[m_stats.indexOf(begin)] : DataEntry{} };
            result.emplace_back(entry);
        }

        return result;
    }

    auto PomodoroStats::size() const -> qsizetype { return m_stats.size(); }


    void PomodoroStats::addPomodoro(std::chrono::seconds pomodoroDuration, const QDate date)
    {
        if (not contains(date))
        {
            m_stats.emplaceBack(date, 1, pomodoroDuration);
            emit newEntryAdded(date);
            return;
        }

        auto &entry{ m_stats[m_stats.indexOf(date)] };

        entry.pomodoros++;
        entry.totalTime += pomodoroDuration;

        emit entryChanged(date);
    }


    void PomodoroStats::removeEntry(const QDate date)
    {
        m_stats.remove(m_stats.indexOf(date));
        emit entryRemoved(date);
    }


    void PomodoroStats::sync()
    {
        m_settings.sync();
    }
}
