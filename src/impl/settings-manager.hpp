#pragma once

#include "pomodoro-timer.hpp"

#include <QObject>
#include <QSettings>


namespace impl
{
    class SettingsManager : public QObject
    {
        Q_OBJECT
        QML_UNCREATABLE("Мне так по кайфу")
        QML_NAMED_ELEMENT(SettingsManager)

        Q_PROPERTY(bool isPomodoroAutoStarEnabled READ isPomodoroAutoStarEnabled NOTIFY autoStartStateChanged)

    public:

        explicit SettingsManager(PomodoroTimer *pt, QObject *parent = nullptr);

        [[nodiscard]] bool isPomodoroAutoStarEnabled() const;

    public slots:

        void setPhaseDuration(PomodoroTimer::Phase phase, u16 seconds);
        void setSessionLength(u16 pomodoros);
        void togglePomodoroAutoStart();
        void readSettings(PomodoroTimer *);
        void writeSettings(PomodoroTimer *);

        void saveAllSettings();

    private slots:

        void enablePomodoroStart(PomodoroTimer::Phase phase) const;

    signals:

        void invalidValuePassed(QString propertyName);
        void autoStartStateChanged(bool);

    private:

        bool m_isPomodoroAutoStarEnabled;
        PomodoroTimer *m_timer;
        QSettings m_settings;
    };
}
