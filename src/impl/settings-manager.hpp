/**
 * @todo Если написать хуергу в конфиге, то `QSettings` попытается переварить выдаст невалидное значение.
 *      Можно попробовать как валидировать значения из конфига
 */

#pragma once

#include <QGuiApplication>

#include "impl/pomodoro-timer.hpp"

#include <QObject>
#include <QSettings>


namespace impl
{
    class SettingsManager : public QObject
    {
        Q_OBJECT

    public:

        explicit SettingsManager(QGuiApplication *app);

        [[nodiscard]] auto getInfoForPomodoroTimer() -> PomodoroTimer::CreateInfo;

        void setupConnections(const PomodoroTimer *pt);

    public slots:

        void sync();

    private:

        QSettings m_settings;
    };
}