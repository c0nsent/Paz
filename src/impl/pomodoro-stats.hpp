#pragma once

#include "core/basic-types-aliases.hpp"

#include <QDate>
#include <QList>
#include <QObject>
#include <qqmlintegration.h>
#include <QSettings>

#include <chrono>


namespace impl
{

    class PomodoroStatsEntry
    {
        Q_GADGET
        QML_NAMED_ELEMENT(pomodoroStatsEntry)

        Q_PROPERTY(QDate date READ date)
        Q_PROPERTY(u16 pomodoros READ pomodoros)
        Q_PROPERTY(i64 totalTime READ totalTime)

    public:

        PomodoroStatsEntry() = default;
        PomodoroStatsEntry(QDate date, u16 pomodoros, std::chrono::seconds totalTime);
        PomodoroStatsEntry(QDate date, u16 pomodoros, i64 totalTimeInSeconds);

        PomodoroStatsEntry(const PomodoroStatsEntry &) = default;

        [[nodiscard]] auto date() const noexcept -> QDate;
        [[nodiscard]] auto pomodoros() const noexcept -> u16;
        [[nodiscard]] auto totalTime() const noexcept -> i64;

        void addPomodoro(std::chrono::seconds duration);
        void addPomodoro(i64 duration);

        auto operator==(const PomodoroStatsEntry &rhs) const noexcept -> bool;
        auto operator==(QDate otherDate) const noexcept -> bool;

    private:

        QDate m_date;
        u16 m_pomodoros;
        std::chrono::seconds m_totalTime;
    };

    class PomodoroStats : public QObject
    {
        Q_OBJECT
        QML_NAMED_ELEMENT(PomodoroStats)

    public:

        explicit PomodoroStats(QObject *parent = nullptr);

        [[nodiscard]] auto contains(QDate date) const noexcept -> bool;
        [[nodiscard]] auto get(QDate date) const noexcept -> PomodoroStatsEntry;
        [[nodiscard]] auto get(QDate begin, QDate end) const -> QList<PomodoroStatsEntry>;
        [[nodiscard]] auto size() const -> qsizetype;

    public slots:

        void addPomodoro(std::chrono::seconds pomodoroDuration);
        void addPomodoro(std::chrono::seconds pomodoroDuration, QDate date);
        void removeEntry(QDate date);
        void sync();

    signals:

        void newEntryAdded(QDate date);
        void entryChanged(QDate date);
        void entryRemoved(QDate date);

    private:

        QSettings m_settings;
        QList<PomodoroStatsEntry> m_stats;
    };
}
