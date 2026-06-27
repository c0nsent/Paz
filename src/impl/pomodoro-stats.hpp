#pragma once

#include "../core/basic-types-aliases.hpp"

#include <QDate>
#include <QObject>
#include <QSettings>


namespace impl
{
    class PomodoroStats : public QObject
    {
    public:

        struct Entry
        {
            QDate date;
            QTime workTime;
            u16 pomodoroFinished;

        };


    public:

        explicit PomodoroStats(QObject *parent=nullptr);



    public slots:



    private:

        QSettings m_stats;
    };
}