#pragma once

#include "impl/pomodoro-stats.hpp"
#include "impl/pomodoro-timer.hpp"
#include "impl/settings-manager.hpp"

#include <QSystemTrayIcon>
#include <QGuiApplication>
#include <QObject>


namespace impl
{
    class Initializer : public QObject
    {
        Q_OBJECT

    public:

        explicit Initializer(QGuiApplication *app);

        [[nodiscard]] auto createPomodoroTimer() -> PomodoroTimer *;
        [[nodiscard]] auto createPomodoroStats() -> PomodoroStats *;
        [[nodiscard]] auto createSystemTrayIcon() -> QSystemTrayIcon *;


    private:

        SettingsManager *m_settingsManager;
    };



}

