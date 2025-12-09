/**
 * @date 12/2/25
 * 
 * @author amitayus_
 */

#pragma once

#include "../../impl/pomodoro-timer.hpp"

#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QSettings>


namespace ui
{
	class PomodoroTimerWidget final : public QWidget
	{
		Q_OBJECT

		static constexpr const char *c_phaseStrings[defaults::c_phaseCount] {"Working", "Short Break", "Long Break"};
		static constexpr const char *c_timerStateStrings[3]{"Start", "Pause", "Resume"};


		void setupWidget();
		//Soviet Connection
		void setupConnections();

		void readSettings();
		void writeSettings();

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

		QSettings *m_settings;

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
