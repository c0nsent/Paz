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
		, m_phase{new QLabel{this}}
		, m_remainingTime{new QLabel{this}}
		, m_phaseProgress{new QProgressBar{this}}
		, m_skip{new QPushButton{this}}
		, m_startPauseButton{new QPushButton{this}}
		, m_reset{new QPushButton{this}}
	{
		m_font.setBold(true);

		m_phaseProgress->setMinimum(0);
		m_phaseProgress->setMaximum(m_timer->currentPhaseDuration());

		m_phase->setFont(m_font);
		m_phase->setAlignment(Qt::AlignCenter);
		m_phase->setFrameStyle(QFrame::Panel | QFrame::Sunken);

		updateRemainingTimeLabel(m_timer->currentPhaseDuration());
		m_remainingTime->setFont(m_font);
		m_remainingTime->setAlignment(Qt::AlignCenter);

		m_skip->setFont(m_font);


		m_mainLayout->addWidget(m_phase);
		m_mainLayout->addWidget(m_remainingTime);
		m_mainLayout->addWidget(m_phaseProgress);
		m_mainLayout->addWidget(m_skip);
		m_mainLayout->addWidget(m_startPauseButton);
		m_mainLayout->addWidget(m_reset);

		connect(m_skip, &QPushButton::clicked, [this]
		{
			m_timer->toNextPhase();
			setStartPauseLabel(startPauseLabel::Start);
		});

		connect(m_startPauseButton, &QPushButton::clicked, [this]
		{
			if (m_timer->isActive())
			{
				setStartPauseLabel(startPauseLabel::Pause);
				m_timer->pause();
			}
			else
			{
				setStartPauseLabel(startPauseLabel::Resume);
				m_timer->start();
			}
		});

		connect(m_reset, &QPushButton::clicked, [this]
		{
			m_timer->reset();
			setStartPauseLabel(startPauseLabel::Start);
		});

		connect(m_timer, &impl::PomodoroTimer::phaseChanged, this, &PomodoroTimerWidget::updatePhase);

		connect(m_timer, &impl::PomodoroTimer::remainingTimeChanged, m_phaseProgress, &QProgressBar::setValue);
		connect(m_timer, &impl::PomodoroTimer::remainingTimeChanged, this, &PomodoroTimerWidget::updateRemainingTimeLabel);
	}


	void PomodoroTimerWidget::updatePhase(const impl::PomodoroTimer::Phase phase)
	{
		static const char *phaseNames[impl::defaults::c_phaseCount] {"Working", "Short Break", "Long Break"};

		m_phase->setText(phaseNames[qToUnderlying(phase)]);
	}


	void PomodoroTimerWidget::setStartPauseLabel(const startPauseLabel label)
	{
		static const char * labels[]{"Start", "Pause", "Resume"};

		m_startPauseButton->setText(labels[qToUnderlying(label)]);
	}


	void PomodoroTimerWidget::updateRemainingTimeLabel(const quint16 remainingTime)
	{
		const auto[minutes, seconds]{toSecondsAndMinutes(remainingTime)};

		m_remainingTime->setText(QString::number(minutes) + ':' + QString::number(seconds));
	}


	void PomodoroTimerWidget::updateStartPauseButtonLabel()
	{
		if (m_timer->isActive())
			setStartPauseLabel(startPauseLabel::Start);
		else
			setStartPauseLabel(startPauseLabel::Pause);
	}
}
