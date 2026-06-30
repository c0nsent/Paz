#pragma once

#include "core/basic-types-aliases.hpp"

#include <QSettings>
#include <QHash>
#include <QList>
#include <QDate>
#include <QTime>
#include <QVarLengthArray>


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
        };

        explicit PomodoroStats(QObject *parent = nullptr);

        [[nodiscard]] auto at(QDate date) -> DataEntry &;
        [[nodiscard]] auto checkout(QDate date) const -> DataEntry;
        [[nodiscard]] bool contains(QDate date) const;
        [[nodiscard]] auto range(QDate begin, QDate end) const -> QVarLengthArray<DataEntry>;
        [[nodiscard]] auto size() const -> size_t;


    public slots:

        void addEntry(QDate date, u16 pomodoros, QTime totalTime);



    private:

        QSettings m_settings;
        QList<DataEntry> m_stats;
    };
}