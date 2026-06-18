#pragma once

#include "pomodoro-timer.hpp"

#include <QtQml/qqmlregistration.h>


struct PomodoroTimerReg
{
    Q_GADGET
    QML_FOREIGN(impl::PomodoroTimer)
    QML_NAMED_ELEMENT(PomodoroTimer)
    QML_ADDED_IN_VERSION(1, 0)
};