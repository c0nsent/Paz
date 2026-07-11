#pragma once

#include "impl/pomodoro-timer.hpp"

#include <QObject>
#include <QSettings>
#include <QTime>


namespace impl
{
    class SettingsManager : public QObject
    {
        Q_OBJECT
        QML_UNCREATABLE("Мне так по кайфу")
        QML_NAMED_ELEMENT(SettingsManager)

        Q_PROPERTY(bool isPomodoroAutoStarEnabled READ isPomodoroAutoStarEnabled NOTIFY autoStartStateChanged)

    public:

        explicit SettingsManager(QObject *parent = nullptr);

        [[nodiscard]] bool isPomodoroAutoStarEnabled() const;

        template<class T>
        auto readSettings() const -> T;

        template<>
        auto readSettings<PomodoroTimer>() const -> PomodoroTimer;



    public slots:

        template<class T>
        void writeSettings();

        template<>
        void writeSettings<PomodoroTimer>();

        void saveAllSettings();

    private slots:


    signals:

        void invalidValuePassed(QString propertyName);

    private:

        QSettings m_settings;
    };



}
