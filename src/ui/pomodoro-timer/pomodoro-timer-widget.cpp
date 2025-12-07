/**
 * @date 12/2/25
 * 
 * @author amitayus_
 */

#include "pomodoro-timer-widget.hpp"


namespace paz::ui::pt
{
	auto PomodoroTimerWidget::toString(const impl::PomodoroTimer::Phase phase) -> const char *
	{
		static const char *phaseNames[impl::defaults::c_phaseCount] {"Working", "Short Break", "Long Break"};

		return phaseNames[qToUnderlying(phase)];
	}


	auto PomodoroTimerWidget::toSecondsAndMinutes(const qint16 seconds) -> QPair<qint16, qint16>
	{
		return { seconds / 60, seconds % 60 };
	}


	QString PomodoroTimerWidget::formatRemainingTime() const
	{
		const auto[minutes, seconds]{ toSecondsAndMinutes(m_timerBackend->remainingTime()) };

		return QString::number(minutes) + ':' + QString::number(seconds);
	}


	PomodoroTimerWidget::PomodoroTimerWidget(QWidget *parent)
	{
		QFont font{"Noto Serif"};
		font.setBold(true);
		font.setPixelSize(24);

		m_timerBackend = new impl::PomodoroTimer{this};
		//m_timerBackend->setAllPhaseDurations(10, 5 ,5);

		m_phaseProgress = new QProgressBar{this};
		m_phaseProgress->setMinimum(0);
		m_phaseProgress->setMaximum(m_timerBackend->currentPhaseDuration());

		m_currentPhase = new QLabel{"Working"};
		m_currentPhase->setFont(font);
		m_currentPhase->setAlignment(Qt::AlignCenter);
		m_currentPhase->setFrameStyle(QFrame::Panel | QFrame::Sunken);

		/*m_timeLayout = new QHBoxLayout{};*/
		m_remainingTime = new QLabel{formatRemainingTime()};
		/*m_remainingMinutes = new QLabel{};
		m_remainingSeconds = new QLabel{};*/

		m_skip = new QPushButton{"Skip"};
		m_skip->setFont(font);
		m_skip->setWhatsThis("asdfkjsd");
		m_startPause = new QPushButton{"Start"};
		m_reset = new QPushButton{"Reset"};

		m_mainLayout = new QVBoxLayout{this};
		m_mainLayout->addWidget(m_currentPhase);
		m_mainLayout->addWidget(m_remainingTime);
		m_mainLayout->addWidget(m_phaseProgress);
		m_mainLayout->addWidget(m_skip);
		m_mainLayout->addWidget(m_startPause);
		m_mainLayout->addWidget(m_reset);

		connect(m_skip, &QPushButton::clicked, [this]
		{
			m_timerBackend->toNextPhase();
			m_startPause->setText("Start");
		});

		connect(m_startPause, &QPushButton::clicked, [this]
		{
			if (m_timerBackend->isActive())
			{
				m_timerBackend->pause();
				m_startPause->setText("Pause");
			}
			else
			{
				m_startPause->setText("Resume");
				m_timerBackend->start();
			}
		});

		connect(m_reset, &QPushButton::clicked, [this]
		{
			m_timerBackend->reset();
			m_startPause->setText("Start");
		});

		connect(m_timerBackend, &impl::PomodoroTimer::phaseChanged, [this] (const impl::PomodoroTimer::Phase phase)
		{
			m_currentPhase -> setText(toString(phase));
		});

		connect(m_timerBackend, &impl::PomodoroTimer::remainingTimeChanged, m_phaseProgress, &QProgressBar::setValue);
		connect(m_timerBackend, &impl::PomodoroTimer::remainingTimeChanged, m_remainingTime, [this] (const quint16 seconds)
		{
			m_remainingTime -> setText(formatRemainingTime());
		});

	}
}
