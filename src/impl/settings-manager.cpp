#include "settings-manager.hpp"

#include <QMetaMethod>
#include <QtMinMax>


namespace impl
{
    SettingsManager::SettingsManager(PomodoroTimer *pt, QObject *parent)
        : QObject{parent}, m_timer{pt}
    {
    }


    void SettingsManager::setPhaseDuration(const PomodoroTimer::Phase phase, const u16 seconds)
    {
        const u16 boundedSeconds{qBound(limits::MIN_PHASE_DURATION, seconds, limits::MAX_PHASE_DURATION)};

        if (seconds != boundedSeconds) emit invalidValuePassed("phaseDuration");

        m_timer->setPhaseDuration(phase, boundedSeconds);
    }


    void SettingsManager::setSessionLength(const u16 pomodoros)
    {
        const u16 boundedPomodoros{qBound(limits::MIN_SESSION_LENGTH, pomodoros, limits::MAX_SESSION_LENGTH)};

        if (pomodoros != boundedPomodoros) emit invalidValuePassed("sessionLength");

        m_timer->setSessionLength(boundedPomodoros);
    }

    void SettingsManager::autoStartNewPomodoro(const bool isTrue)
    {
        static auto timeIsOutSignal{QMetaMethod::fromSignal(&PomodoroTimer::timeIsOut)};

        if (isTrue)
        {
            if (isSignalConnected(timeIsOutSignal)) return;

            connect(m_timer, &PomodoroTimer::timeIsOut, this, [&]
            {
                if (m_timer->phase() == PomodoroTimer::Phase::Work) m_timer->start();
            });
        }
        else
        {
            if (not isSignalConnected(timeIsOutSignal)) return;

            disconnect(m_timer, &PomodoroTimer::timeIsOut, this, nullptr);
        }
    }


    void SettingsManager::readSettings(const PomodoroTimer &)
    {
        using enum PomodoroTimer::Phase;

        m_settings.beginGroup(settings::groups::POMODORO_TIMER);
        m_timer->setPhaseDuration(Work,m_settings.value("WorkDuration", 25 * 60).toUInt());
        m_timer->setPhaseDuration(ShortBreak, m_settings.value("ShortBreakDuration", 5 * 60).toUInt());
        m_timer->setPhaseDuration(LongBreak, m_settings.value("LongBreakDuration", 40 * 60).toUInt());
        m_timer->setSessionLength(m_settings.value("SessionLength",8).toUInt());
        autoStartNewPomodoro(m_settings.value("AutoStartNewPomodoro", true).toBool());
        m_settings.endGroup();
    }


    void SettingsManager::writeSettings(const PomodoroTimer &)
    {
        using enum PomodoroTimer::Phase;

        m_settings.beginGroup(settings::groups::POMODORO_TIMER);
        m_settings.setValue("WorkDuration", m_timer->phaseDuration(Work));
        m_settings.setValue("ShortBreakDuration", m_timer->phaseDuration(ShortBreak));
        m_settings.setValue("LongBreakDuration", m_timer->phaseDuration(LongBreak));
        m_settings.setValue("SessionLength", m_timer->sessionLength());

        static auto timeIsOutSignal{QMetaMethod::fromSignal(&PomodoroTimer::timeIsOut)};

        qDebug() << "AutoStartNewPomodoro: " << isSignalConnected(timeIsOutSignal);
        m_settings.setValue("AutoStartNewPomodoro", isSignalConnected(timeIsOutSignal));

        m_settings.endGroup();
    }


    void SettingsManager::saveAllSettings()
    {
        writeSettings(*m_timer);
    }
}
