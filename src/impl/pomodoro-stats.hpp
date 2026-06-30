#pragma once

#include "core/basic-types-aliases.hpp"

#include <QSettings>
#include <QHash>
#include <QList>
#include <QDate>
#include <QObject>
#include <QVariant>
#include <QTime>
#include <QVarLengthArray>

#include <optional>


namespace impl
{


    class PomodoroStats : public QObject
    {
    public:

        struct DataEntry
        {
            QDate date;
            u16 pomodoros;
            QTime totalTime;

            bool operator==(const DataEntry &rhs) const;
            bool operator==(QDate otherDate) const;
        };

        explicit PomodoroStats(QObject *parent = nullptr);

    [[nodiscard]] auto at(QDate date) -> std::optional<DataEntry &>;
        [[nodiscard]] auto checkout(QDate date) const -> std::optional<DataEntry>;
        [[nodiscard]] bool contains(QDate date) const;
        [[nodiscard]] auto range(QDate begin, QDate end) const -> QVarLengthArray<DataEntry>;
        [[nodiscard]] auto size() const -> size_t;

    public slots:

        //void addEntry(QDate date, u16 pomodoros, QTime totalTime);
        void addPomodoro(QTime pomodoroDuration, QDate date=QDate::currentDate());
        void sync();

    signals:

        void entryAdded(QDate date);
        void entryChanged(QDate date);

    private:

        QSettings m_settings;
        QList<DataEntry> m_stats;
    };
}