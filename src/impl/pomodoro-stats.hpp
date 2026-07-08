#pragma once

#include "core/basic-types-aliases.hpp"

#include <QSettings>
#include <QHash>
#include <QList>
#include <QDate>
#include <QObject>
#include <QVariant>
#include <QTime>

#include <chrono>
#include <optional>


namespace impl
{


    class PomodoroStats : public QObject
    {
    public:

        struct DataEntry
        {
            QDate date;
            u16 pomodoros{0};
            std::chrono::seconds totalTime{0};

            bool operator==(const DataEntry &rhs) const noexcept;
            bool operator==(QDate otherDate) const noexcept;
        };

        explicit PomodoroStats(QObject *parent = nullptr);

        [[nodiscard]] auto contains(QDate date) const noexcept -> bool;
        [[nodiscard]] auto get(QDate date) const -> DataEntry;
        [[nodiscard]] auto get(QDate begin, QDate end) const -> QList<DataEntry>;
        [[nodiscard]] auto size() const -> qsizetype;

    public slots:

        //void addEntry(QDate date, u16 pomodoros, QTime totalTime);
        void addPomodoro(std::chrono::seconds pomodoroDuration, QDate date=QDate::currentDate());
        void removeEntry(QDate date);
        void sync();

    signals:

        void newEntryAdded(QDate date);
        void entryChanged(QDate date);
        void entryRemoved(QDate date);

    private:

        QSettings m_settings;
        QList<DataEntry> m_stats;
    };
}