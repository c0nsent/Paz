#pragma once

#include "impl/pomodoro-stats.hpp"
#include "impl/pomodoro-timer.hpp"
#include "impl/settings-manager.hpp"

#include <QGuiApplication>
#include <QObject>


namespace impl
{
    class Initializer : public QObject
    {
        Q_OBJECT

    public:

        explicit Initializer(QGuiApplication *app);

        auto createPomodoroTimer() -> PomodoroTimer *;
        auto createPomodoroStats() -> PomodoroStats *;


    private:

        SettingsManager m_settingsManager;
    };



}

