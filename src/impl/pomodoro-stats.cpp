#include "pomodoro-stats.hpp"
#include "core/constants.hpp"

#include <QGuiApplication>

namespace impl
{
    bool PomodoroStats::DataEntry::operator==(const DataEntry& rhs) const
    {
        return date == rhs.date;
    }

    bool PomodoroStats::DataEntry::operator==(const QDate otherDate) const
    {
        return this->date == otherDate;
    }

    PomodoroStats::PomodoroStats(QObject *parent)
        : QObject{parent}
        , m_settings{QGuiApplication::organizationDomain(), "Statistics"}
    {


    }

    auto PomodoroStats::at(const QDate date) -> DataEntry &
    {
        if (not contains(date)) throw std::out_of_range{"error: impl::PomodoroStats::at() reached out of range"};

        return m_stats[m_stats.indexOf(date)];
    }

    auto PomodoroStats::checkout(QDate date) const -> std::optional<DataEntry>
    {

    }

    bool PomodoroStats::contains(const QDate date) const
    {
        return m_stats.contains(date);
    }

    auto PomodoroStats::range(QDate begin, QDate end) const -> QVarLengthArray<DataEntry>
    {
    }

    auto PomodoroStats::size() const -> size_t
    {
        return m_stats.size();
    }

    void PomodoroStats::addPomodoro(QTime pomodoroDuration, QDate date)
    {
    }

    void PomodoroStats::sync()
    {
        m_settings.sync();
    }
}
