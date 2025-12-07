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

		static auto toSecondsAndMinutes(quint16 seconds) -> QPair<qint16, qint16>;

	public:

		enum class startPauseLabel : quint8 { Start, Pause, Resume };

		explicit PomodoroTimerWidget(QWidget *parent = nullptr);

		//auto getTimer() -> impl::PomodoroTimer & { return *m_timerBackend; }

	private slots:

		void updatePhase(impl::PomodoroTimer::Phase phase);
		void setStartPauseLabel(startPauseLabel label);

		void updateRemainingTimeLabel(quint16 remainingTime);
		void updateStartPauseButtonLabel();

	private:

		impl::PomodoroTimer *m_timer;

		QFont m_font;

		QVBoxLayout *m_mainLayout;

		QLabel *m_phase;
		QLabel *m_remainingTime;
		QProgressBar *m_phaseProgress;
		QPushButton *m_skip;
		QPushButton *m_startPauseButton;
		QPushButton *m_reset;
	};
}
