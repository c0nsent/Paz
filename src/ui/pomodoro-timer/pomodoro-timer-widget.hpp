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

		static constexpr const char *c_phaseStrings[impl::defaults::c_phaseCount] {"Working", "Short Break", "Long Break"};
		static constexpr const char *c_timerStateStrings[3]{"Start", "Pause", "Resume"};

	public:

		explicit PomodoroTimerWidget(QWidget *parent = nullptr);

	public slots:

		void setupWidget();
		//Soviet Connection
		void setupConnections();

	private slots:

		void updatePhaseLabelText();
		void updateStartPauseButtonText(impl::PomodoroTimer::State current);
		void updateRemainingTimeText(quint16 current);
		void updatePhaseProgress();
		void updatePomodoroCountText();

	private:

		impl::PomodoroTimer *m_timer;

		QFont m_font;

		QVBoxLayout *m_mainLayout;

		QLabel *m_phase;
		QLabel *m_remainingTime;
		QProgressBar *m_phaseProgress;
		QLabel *m_pomodoroCount;
		QPushButton *m_skipButton;
		QPushButton *m_startPauseButton;
		QPushButton *m_reset;
	};
}
