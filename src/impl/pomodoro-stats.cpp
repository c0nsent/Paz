#include "pomodoro-stats.hpp"
#include "core/constants.hpp"

#include <QGuiApplication>

namespace impl
{



    PomodoroStats::PomodoroStats(QObject *parent)
    {
        QSettings settings{QGuiApplication::organizationDomain(), "Statistics"};


    }
}