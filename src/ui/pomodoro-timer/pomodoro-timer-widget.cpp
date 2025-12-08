/**
 * @date 12/2/25
 * 
 * @author amitayus_
 */

#include "pomodoro-timer-widget.hpp"


namespace paz::ui::pt
{
	PomodoroTimerWidget::PomodoroTimerWidget(QWidget *parent)
		: QWidget{parent}
		, m_timer{new impl::PomodoroTimer{this}}
		, m_font{"Noto Serif", 24}
		, m_mainLayout{new QVBoxLayout{this}}
		, m_phase{new QLabel{ this}}
		, m_remainingTime{new QLabel{this}}
		, m_phaseProgress{new QProgressBar{this}}
		, m_pomodoroCount{new QLabel{this}}
		, m_skipButton{new QPushButton{this}}
		, m_startPauseButton{new QPushButton{this}}
		, m_reset{new QPushButton{this}}
	{
		setupWidget();
		setupConnections();
	}


	void PomodoroTimerWidget::setupWidget()
	{
		m_font.setBold(true);

		updatePhaseLabelText();
		updateRemainingTimeText(m_timer->phaseDuration());
		updatePhaseLabelText();
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

		m_mainLayout->addWidget(m_phase);
		m_mainLayout->addWidget(m_remainingTime);
		m_mainLayout->addWidget(m_phaseProgress);
		m_mainLayout->addWidget(m_pomodoroCount);
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


	void PomodoroTimerWidget::updatePhaseLabelText()
	{
		m_phase->setText(c_phaseStrings[qToUnderlying(m_timer->phase())]);
	}


	void PomodoroTimerWidget::updateStartPauseButtonText(const impl::PomodoroTimer::State current)
	{
		m_startPauseButton->setText(c_timerStateStrings[qToUnderlying(current)]);
	}


	void PomodoroTimerWidget::updateRemainingTimeText(const quint16 current)
	{
		const auto minutes { current / 60 };
		const auto seconds { current % 60 };

		m_remainingTime->setText(QString::asprintf("%d:%02d", minutes, seconds));
	}


	void PomodoroTimerWidget::updatePhaseProgress()
	{
		m_phaseProgress->setMinimum(0);
		m_phaseProgress->setMaximum(m_timer->phaseDuration());
		m_phaseProgress->setValue(m_timer->phaseDuration());
	}


	void PomodoroTimerWidget::updatePomodoroCountText()
	{
		static qint16 pomodoroCount{-1};
		pomodoroCount++;

		auto text{QString{"%1 pomodoro"}.arg(pomodoroCount)};

		if ( pomodoroCount > 2) text + 's';

		m_pomodoroCount->setText(text);
	}
}
