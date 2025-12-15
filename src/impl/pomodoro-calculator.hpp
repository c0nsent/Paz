#pragma once

#include "../core/constants.hpp"

#include <QSettings>
#include <QString>
#include <QTime>


namespace impl
{
	class PomodoroCalculator
	{
		void readSettings();

	public:

		[[nodiscard]] QTime calculate(quint16 repeatCount);

	private:

		QSettings m_settings{ QSettings::UserScope, settings::c_org, settings::c_app };

		quint16 m_workDuration{};
		quint16 m_shortBreakDuration{};
		quint16 m_longBreakDuration{};

		quint16 m_session_count{};
	};
}
