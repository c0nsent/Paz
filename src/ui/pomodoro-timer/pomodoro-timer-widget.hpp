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


		static auto toSecondsAndMinutes(quint16 seconds) -> QPair<qint16, qint16>;

	public:

		explicit PomodoroTimerWidget(QWidget *parent = nullptr);


	public slots:

		void setupWidget();
		//Soviet Connection
		void setupConnections();

	private slots:

		void setText(impl::PomodoroTimer::Phase phase);
		void setText(impl::PomodoroTimer::State state);

		void updateRemainingTimeText(quint16 remainingTime);

	private:

		impl::PomodoroTimer *m_timer;

		QFont m_font;

		QVBoxLayout *m_mainLayout;

		QLabel *m_phase;
		QLabel *m_remainingTime;
		QProgressBar *m_phaseProgress;
		QPushButton *m_skipButton;
		QPushButton *m_startPauseButton;
		QPushButton *m_reset;
	};
}
