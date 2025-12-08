/**
 * @date 12/2/25
 * 
 * @author amitayus_
 */

#include "pomodoro-timer-widget.hpp"


namespace paz::ui::pt
{
	auto PomodoroTimerWidget::toSecondsAndMinutes(const quint16 seconds) -> QPair<qint16, qint16>
	{
		return { seconds / 60, seconds % 60 };
	}


	PomodoroTimerWidget::PomodoroTimerWidget(QWidget *parent)
		: QWidget{parent}
		, m_timer{new impl::PomodoroTimer{this}}
		, m_font{"Noto Serif", 24}
		, m_mainLayout{new QVBoxLayout{this}}
		, m_phase{new QLabel{ this}}
		, m_remainingTime{new QLabel{this}}
		, m_phaseProgress{new QProgressBar{this}}
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

		m_phase->setText(c_phaseStrings[qToUnderlying(m_timer->phase())]);
		m_phase->setFont(m_font);
		m_phase->setAlignment(Qt::AlignCenter);
		m_phase->setFrameStyle(QFrame::Panel | QFrame::Sunken);

		updateRemainingTimeText(m_timer->phaseDuration());
		m_remainingTime->setFont(m_font);
		m_remainingTime->setAlignment(Qt::AlignCenter);

		m_phaseProgress->setMinimum(0);
		m_phaseProgress->setMaximum(m_timer->phaseDuration());

		m_skipButton->setText("Skip");
		m_skipButton->setFont(m_font);

		m_startPauseButton->setText(c_timerStateStrings[qToUnderlying(m_timer->state())]);
		m_startPauseButton->setFont(m_font);

		m_reset->setText("Reset");
		m_reset->setFont(m_font);

		m_mainLayout->addWidget(m_phase);
		m_mainLayout->addWidget(m_remainingTime);
		m_mainLayout->addWidget(m_phaseProgress);
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
			QOverload<impl::PomodoroTimer::Phase>::of(&PomodoroTimerWidget::setText)
		);

		connect(m_timer, &impl::PomodoroTimer::remainingTimeChanged, this, &PomodoroTimerWidget::updateRemainingTimeText);

		connect(m_skipButton, &QPushButton::clicked, [this]
		{
			m_timer->toNextPhase();
		});

		connect(m_startPauseButton, &QPushButton::clicked, [this]
		{
			m_timer->isActive() ? m_timer->pause() : m_timer->start();
		});

		connect(m_reset, &QPushButton::clicked, [this]
		{
			m_timer->reset();
			setText(impl::PomodoroTimer::State::Idle);
		});

		connect(m_timer, &impl::PomodoroTimer::remainingTimeChanged, m_phaseProgress, &QProgressBar::setValue);

	}


	void PomodoroTimerWidget::setText(const impl::PomodoroTimer::Phase phase)
	{
		m_phase->setText(c_phaseStrings[qToUnderlying(phase)]);
	}


	void PomodoroTimerWidget::setText(const impl::PomodoroTimer::State state)
	{
		m_startPauseButton->setText(c_timerStateStrings[qToUnderlying(state)]);
	}


	void PomodoroTimerWidget::updateRemainingTimeText(const quint16 remainingTime)
	{
		const auto minutes { remainingTime / 60 };
		const auto seconds { remainingTime % 60 };

		m_remainingTime->setText(QString::number(minutes) + ':' + QString::number(seconds));
	}

}
