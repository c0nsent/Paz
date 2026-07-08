#pragma once

#include "core/basic-types-aliases.hpp"

#include <QSettings>
#include <QList>
#include <QDate>
#include <QObject>
#include <qqmlintegration.h>

#include <chrono>


namespace impl
{

    struct PomodoroStatsEntry
    {
        Q_GADGET
        QML_NAMED_ELEMENT(pomodoroStatsEntry)

        Q_PROPERTY(QDate date READ date)
        Q_PROPERTY(u16 pomodoros MEMBER pomodoros)
        Q_PROPERTY(i64 totalTime READ getTotalTime WRITE setTotalTime)

    public:

        QDate date;
        u16 pomodoros{0};
        std::chrono::seconds totalTime{0};

        [[nodiscard]] auto getTotalTime() const noexcept -> i64;
        void setTotalTime(i64 seconds) noexcept;

        auto operator==(const PomodoroStatsEntry &rhs) const noexcept -> bool;
        auto operator==(QDate otherDate) const noexcept -> bool;
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

        void addPomodoro(std::chrono::seconds pomodoroDuration, QDate date=QDate::currentDate());
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
