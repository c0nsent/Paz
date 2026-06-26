#include "settings-manager.hpp"

#include "core/constants.hpp"

#include <QMetaMethod>
#include <QtMinMax>


namespace impl
{
    SettingsManager::SettingsManager(PomodoroTimer *pt, QObject *parent) : QObject{parent}, m_timer{pt}
    {
        using namespace settings;
        m_settings.beginGroup(grps::POMODORO_TIMER);
        m_isPomodoroAutoStarEnabled
                = m_settings.value(keys::AUTOSTART_NEW_POMODORO, defaults::AUTOSTART_NEW_POMODORO).toBool();
        m_settings.endGroup();
    }


    bool SettingsManager::isPomodoroAutoStarEnabled() const { return m_isPomodoroAutoStarEnabled; }


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


    void SettingsManager::togglePomodoroAutoStart()
    {
        m_isPomodoroAutoStarEnabled = not m_isPomodoroAutoStarEnabled;

        if (m_isPomodoroAutoStarEnabled)
            connect(m_timer, &PomodoroTimer::timerFinished, this, &SettingsManager::enablePomodoroStart);
        else
            disconnect(m_timer, &PomodoroTimer::timerFinished, this, &SettingsManager::enablePomodoroStart);
    }


    void SettingsManager::readSettings(const PomodoroTimer &)
    {
        using enum PomodoroTimer::Phase;
        using namespace settings;

        m_settings.beginGroup(grps::POMODORO_TIMER);
        m_timer->setPhaseDuration(Work,m_settings.value(keys::WORK_DURATION, defaults::WORK_DURATION).toUInt());
        m_timer->setPhaseDuration(ShortBreak, m_settings.value(keys::SHORT_BREAK_DURATION, defaults::SHORT_BREAK_DURATION).toUInt());
        m_timer->setPhaseDuration(LongBreak, m_settings.value(keys::LONG_BREAK_DURATION, defaults::LONG_BREAK_DURATION).toUInt());
        m_timer->setSessionLength(m_settings.value(keys::SESSION_LENGTH,defaults::SESSION_LENGTH).toUInt());
        m_isPomodoroAutoStarEnabled = m_settings.value(keys::AUTOSTART_NEW_POMODORO, defaults::AUTOSTART_NEW_POMODORO).toBool();
        m_settings.endGroup();
    }

    void SettingsManager::writeSettings(const PomodoroTimer &)
    {
        using enum PomodoroTimer::Phase;
        using namespace settings::keys;

        m_settings.beginGroup(settings::grps::POMODORO_TIMER);
        m_settings.setValue(WORK_DURATION, m_timer->phaseDuration(Work));
        m_settings.setValue(SHORT_BREAK_DURATION, m_timer->phaseDuration(ShortBreak));
        m_settings.setValue(LONG_BREAK_DURATION, m_timer->phaseDuration(LongBreak));
        m_settings.setValue(SESSION_LENGTH, m_timer->sessionLength());

        static auto timeIsOutSignal{QMetaMethod::fromSignal(&PomodoroTimer::timerFinished)};

        qDebug() << "AutoStartNewPomodoro: " << isSignalConnected(timeIsOutSignal);
        m_settings.setValue(AUTOSTART_NEW_POMODORO, isSignalConnected(timeIsOutSignal));

        m_settings.endGroup();
    }


    void SettingsManager::saveAllSettings()
    {
        writeSettings(*m_timer);
        m_settings.sync();
    }

    void SettingsManager::enablePomodoroStart(const PomodoroTimer::Phase phase) const
    {
        if (phase == PomodoroTimer::Phase::Work) m_timer->start();
    }
}
