#include "settings-manager.hpp"


namespace impl
{
    SettingsManager::SettingsManager(QGuiApplication *app) : QObject{app} {}


    auto SettingsManager::getInfoForPomodoroTimer() -> PomodoroTimer::CreateInfo
    {
        using enum PomodoroTimer::Phase;
        using namespace settings;

        m_settings.beginGroup(grps::POMODORO_TIMER);
        const PomodoroTimer::CreateInfo createInfo {
            .workPhaseDuration = m_settings.value(keys::WORK_DURATION, defaults::WORK_DURATION).toTime(),
            .shortBreakDuration = m_settings.value(keys::SHORT_BREAK_DURATION, defaults::SHORT_BREAK_DURATION).toTime(),
            .longBreakDuration = m_settings.value(keys::LONG_BREAK_DURATION, defaults::LONG_BREAK_DURATION).toTime(),
            .sessionLength = static_cast<u16>(m_settings.value(keys::SESSION_LENGTH, defaults::SESSION_LENGTH).toUInt()),
            .isAutoStartEnabled = m_settings.value(keys::AUTOSTART_NEW_POMODORO, defaults::AUTOSTART_NEW_POMODORO).toBool()
        };
        m_settings.endGroup();

        return createInfo;
    }


    void SettingsManager::setupConnections(const PomodoroTimer *const pt)
    {
        using namespace settings::keys;

        m_settings.beginGroup(settings::grps::POMODORO_TIMER);

        connect(pt, &PomodoroTimer::workDurationChanged, [&] (const QTime duration)
        {
            m_settings.setValue(WORK_DURATION, duration);
        });
        connect(pt, &PomodoroTimer::shortBreakDurationChanged, [&] (const QTime duration)
        {
           m_settings.setValue(SHORT_BREAK_DURATION, duration);
        });
        connect(pt, &PomodoroTimer::longBreakDurationChanged, [&] (const QTime duration)
        {
           m_settings.setValue(LONG_BREAK_DURATION, duration);
        });
        connect(pt, &PomodoroTimer::sessionLengthChanged, [&] (const u16 pomodoros)
        {
            m_settings.setValue(SESSION_LENGTH, pomodoros);
        });
        connect(pt, &PomodoroTimer::pomodoroAutoStartChanged, [&] (const bool isEnabled)
        {
           m_settings.setValue(AUTOSTART_NEW_POMODORO, isEnabled);
        });

        m_settings.endGroup();
    }


    void SettingsManager::sync() { m_settings.sync(); }
}
