/**
 * @date 12/2/25
 * 
 * @author amitayus_
 */

#pragma once

#include "../impl/pomodoro-timer.hpp"

#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>
#include <QWidget>


namespace ui
{
	class PomodoroTimerWidget final : public QWidget
	{
		Q_OBJECT

		static constexpr const char *c_phaseStrings[defaults::c_phaseCount] { "Working", "Short Break", "Long Break" };
		static constexpr const char *c_timerStateStrings[defaults::c_timerStateCount] { "Start", "Pause", "Resume" };

		void setupWidget();

		void setupConnections();

		void readSettings();
		void writeSettings();

	public:

		explicit PomodoroTimerWidget(QWidget *parent = nullptr);

	public slots:

	private slots:

		void updatePhaseLabelText(impl::PomodoroTimer::Phase current);
		void updateStartPauseButtonText(impl::PomodoroTimer::State current);
		void updateRemainingTimeText(quint16 current);
		void updatePhaseProgress();
		void updatePomodoroCountText();
		void updateSkipBreakButtonVisibility(impl::PomodoroTimer::Phase current);

	private:

		QSettings *m_settings{new QSettings{QSettings::UserScope, "consent_", "Paz"}};

		impl::PomodoroTimer *m_timer{new impl::PomodoroTimer{this}};
		quint16 m_completedPomodoros{0};

		QFont m_font;

		QVBoxLayout *m_mainLayout{new QVBoxLayout{this}};

		QLabel *m_phaseLabel{new QLabel{this}};
		QLabel *m_remainingTimeLabel{new QLabel{this}};
		QProgressBar *m_phaseProgress{new QProgressBar{this}};
		QLabel *m_completedPomodorosLabel{new QLabel{this}};
		QPushButton *m_startPauseButton{new QPushButton{this}};
		QPushButton *m_skipBreakButton{new QPushButton{this}};
		QPushButton *m_resetButton{new QPushButton{this}};
	};
}
