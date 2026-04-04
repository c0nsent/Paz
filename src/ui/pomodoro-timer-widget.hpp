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

		static constexpr const char *c_phaseStrings[defaults::PHASE_COUNT] { "Working", "Short Break", "Long Break" };
		static constexpr const char *c_timerStateStrings[defaults::TIMER_STATE_COUNT] { "Start", "Pause", "Resume" };

		void setupWidget();

		void setupConnections();

		void readSettings();
		void writeDefaultSettings() const;

	public:

		explicit PomodoroTimerWidget(QWidget *parent = nullptr);

	private slots:

		void updatePhaseLabelText(impl::PomodoroTimer::Phase current) const;
		void updateStartPauseButtonText(impl::PomodoroTimer::State current) const;
		void updateRemainingTimeText(quint16 current) const;
		void updatePhaseProgress() const;
		void updatePomodoroCountText();
		void updateSkipBreakButtonVisibility(impl::PomodoroTimer::Phase current) const;

	private:

		QSettings *m_settings{new QSettings{QSettings::UserScope, "consent_", "Paz"}};
		QMetaEnum phaseMeta{ QMetaEnum::fromType<impl::PomodoroTimer::Phase>() };

		impl::PomodoroTimer *m_timer{new impl::PomodoroTimer{{.parent = this }}};
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
