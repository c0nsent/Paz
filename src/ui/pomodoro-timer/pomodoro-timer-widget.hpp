/**
 * @date 12/2/25
 * 
 * @author amitayus_
 */

#pragma once

#include "../../impl/pomodoro-timer.hpp"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar> // For future use
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include <functional>
#include <optional>


namespace paz::ui::pt
{
	class PomodoroTimerWidget final : public QWidget
	{
		Q_OBJECT

		static auto toString(impl::PomodoroTimer::Phase phase) -> const char *;
		static auto toSecondsAndMinutes(qint16 seconds) -> QPair<qint16, qint16>;

		[[nodiscard]] QString formatRemainingTime() const;

	public:

		explicit PomodoroTimerWidget(QWidget *parent = nullptr);

		auto getTimer() -> impl::PomodoroTimer & { return *m_timerBackend; }



	private:

		impl::PomodoroTimer *m_timerBackend;

		QVBoxLayout *m_mainLayout;

		QLabel *m_currentPhase;

		QHBoxLayout *m_timeLayout;
		QLabel *m_remainingTime;
		/*QLabel *m_remainingMinutes;
		QLabel *m_remainingSeconds;*/

		QProgressBar *m_phaseProgress;

		QPushButton *m_skip;
		QPushButton *m_startPause;
		QPushButton *m_reset;
	};
}
