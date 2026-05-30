#pragma once

#include "../core/core"

#include <QSettings>
#include <QTime>


namespace impl
{
	class PomodoroCalculator
	{
		void readSettings();

	public:

		[[nodiscard]] QTime calculate(u16 repeatCount);

	private:

		QSettings m_settings{QSettings::UserScope};

		u16 m_workDuration{};
		u16 m_shortBreakDuration{};
		u16 m_longBreakDuration{};

		u16 m_session_count{};
	};
}
