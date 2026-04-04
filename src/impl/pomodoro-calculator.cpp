#include "pomodoro-calculator.hpp"

#include <QMetaEnum>

namespace impl
{
	void PomodoroCalculator::readSettings()
	{
		m_settings.beginGroup(settings::groups::POMODORO_TIMER);

		auto i{0};

		m_workDuration = m_settings.value(settings::keys::PHASE_DURATIONS.at(i++)).toUInt();
		m_shortBreakDuration = m_settings.value(settings::keys::PHASE_DURATIONS.at(i++)).toUInt();
		m_longBreakDuration = m_settings.value(settings::keys::PHASE_DURATIONS.at(i)).toUInt();
		m_session_count = m_settings.value(settings::keys::SESSION_LENGTH).toUInt();

		m_settings.endGroup();
	}


	QTime PomodoroCalculator::calculate(const u16 repeatCount)
	{
		readSettings();

		QTime result{ QTime::currentTime() };

		const auto oneRepeat{
			(m_workDuration + m_shortBreakDuration) * m_session_count - m_shortBreakDuration
		};

		for (auto i{0}; i != repeatCount - 1; ++i)
		{
			result = result.addSecs(oneRepeat + m_longBreakDuration);
		}

		return result.addSecs(oneRepeat);
	}
}

