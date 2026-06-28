#pragma once

#include "../core/basic-types-aliases.hpp"

#include <QDate>
#include <QObject>
#include <QSettings>


namespace impl
{
    class PomodoroStats : public QObject
    {

        struct DataContainment
        {
            QTime workTime;
            u16 pomodoroFinished;
        };

    public:

        class Entry;



    public:

        explicit PomodoroStats(QObject *parent=nullptr);



    public slots:



    private:

        QHash<QDate, DataContainment> m_data;
        QSettings m_stats;
    };

    class PomodoroStats::Entry
    {
    public:

    private:


    };
}


