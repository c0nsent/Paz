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
#include <QProgressBar>
#include <QVBoxLayout>
#include <QLabel>


namespace paz::ui::pt
{
	class PomodoroTimerWidget final : public QWidget
	{
		Q_OBJECT

		static constexpr const char *c_phaseStrings[impl::defaults::c_phaseCount] {"Working", "Short Break", "Long Break"};
		static constexpr const char *c_timerStateStrings[3]{"Start", "Pause", "Resume"};


		void setupWidget();
		//Soviet Connection
		void setupConnections();

	public:

		explicit PomodoroTimerWidget(QWidget *parent = nullptr);

	public slots:

	private slots:

		void updatePhaseLabelText();
		void updateStartPauseButtonText(impl::PomodoroTimer::State current);
		void updateRemainingTimeText(quint16 current);
		void updatePhaseProgress();
		void updatePomodoroCountText();

	private:

		impl::PomodoroTimer *m_timer;
		quint16 m_completedPomodoros;

		QFont m_font;

		QVBoxLayout *m_mainLayout;

		QLabel *m_phaseLabel;
		QLabel *m_remainingTimeLabel;
		QProgressBar *m_phaseProgress;
		QLabel *m_completedPomodorosLabel;
		QPushButton *m_skipButton;
		QPushButton *m_startPauseButton;
		QPushButton *m_reset;
	};
}
