/**
 * @date 12/2/25
 * 
 * @author amitayus_
 */

#include "pomodoro-timer-widget.hpp"


namespace paz::ui::pt
{
	void PomodoroTimerWidget::setupWidget()
	{
		m_timer->setAllPhaseDurations(5, 5, 5);
		m_font.setBold(true);

		updatePhaseLabelText();
		updateRemainingTimeText(m_timer->phaseDuration());
		updatePhaseProgress();
		updatePomodoroCountText();

		m_skipButton->setText("Skip");
		updateStartPauseButtonText(m_timer->state());
		m_reset->setText("Reset");

		const auto labels{this->findChildren<QLabel *>()};
		for (const auto label : labels)
		{
			label->setFont(m_font);
			label->setAlignment(Qt::AlignCenter);
		}

		const auto buttons{this->findChildren<QPushButton *>()};
		for (const auto button : buttons)
		{
			button->setFont(m_font);
		}

		m_mainLayout->addWidget(m_phaseLabel);
		m_mainLayout->addWidget(m_remainingTimeLabel);
		m_mainLayout->addWidget(m_phaseProgress);
		m_mainLayout->addWidget(m_completedPomodorosLabel);
		m_mainLayout->addWidget(m_skipButton);
		m_mainLayout->addWidget(m_startPauseButton);
		m_mainLayout->addWidget(m_reset);
	}


	void PomodoroTimerWidget::setupConnections()
	{
		connect(
			m_timer,
			&impl::PomodoroTimer::phaseChanged,
			this,
			&PomodoroTimerWidget::updatePhaseLabelText
		);

		connect(
			m_timer,
			&impl::PomodoroTimer::remainingTimeChanged,
			this,
			&PomodoroTimerWidget::updateRemainingTimeText
		);


		connect(m_timer, &impl::PomodoroTimer::remainingTimeChanged, m_phaseProgress, &QProgressBar::setValue);
		connect(m_timer, &impl::PomodoroTimer::phaseChanged, this, &PomodoroTimerWidget::updatePhaseProgress);
		connect(m_timer, &impl::PomodoroTimer::pomodoroFinished, this, &PomodoroTimerWidget::updatePomodoroCountText);
		connect(m_skipButton, &QPushButton::clicked, m_timer, &impl::PomodoroTimer::toNextPhase);

		connect(m_startPauseButton, &QPushButton::clicked, [this]
		{
			m_timer->isActive() ? m_timer->pause() : m_timer->start();
		});

		connect(m_reset, &QPushButton::clicked, m_timer, &impl::PomodoroTimer::reset);
	}


	PomodoroTimerWidget::PomodoroTimerWidget(QWidget *parent)
		: QWidget{parent}
		, m_timer{new impl::PomodoroTimer{this}}
		, m_completedPomodoros{0}
		, m_font{"Noto Serif", 24}
		, m_mainLayout{new QVBoxLayout{this}}
		, m_phaseLabel{new QLabel{ this}}
		, m_remainingTimeLabel{new QLabel{this}}
		, m_phaseProgress{new QProgressBar{this}}
		, m_completedPomodorosLabel{new QLabel{this}}
		, m_skipButton{new QPushButton{this}}
		, m_startPauseButton{new QPushButton{this}}
		, m_reset{new QPushButton{this}}
	{
		setupWidget();
		setupConnections();
	}


	void PomodoroTimerWidget::updatePhaseLabelText()
	{
		m_phaseLabel->setText(c_phaseStrings[qToUnderlying(m_timer->phase())]);
	}


	void PomodoroTimerWidget::updateStartPauseButtonText(const impl::PomodoroTimer::State current)
	{
		m_startPauseButton->setText(c_timerStateStrings[qToUnderlying(current)]);
	}


	void PomodoroTimerWidget::updateRemainingTimeText(const quint16 current)
	{
		const auto minutes { current / 60 };
		const auto seconds { current % 60 };

		m_remainingTimeLabel->setText(QString::asprintf("%d:%02d", minutes, seconds));
	}


	void PomodoroTimerWidget::updatePhaseProgress()
	{
		m_phaseProgress->setMinimum(0);
		m_phaseProgress->setMaximum(m_timer->phaseDuration());
		m_phaseProgress->setValue(m_timer->phaseDuration());
	}


	void PomodoroTimerWidget::updatePomodoroCountText()
	{
		const auto suffix{ (m_completedPomodoros > 1 ) ? QStringLiteral("s") : QString{} };

		m_completedPomodorosLabel->setText(QStringLiteral("%1 pomodoro%2")
			.arg(QString::number(m_completedPomodoros++), suffix));

		//m_completedPomodorosLabel->setText(tr("%n pomodoro(s)", nullptr, m_completedPomodoros++));
	}
}
