/**
 * @date 11/24/25
 * 
 * @author amitayus_
 */

#include "pomodoro-timer.hpp"


namespace paz::impl::pt
{
	void PomodoroTimer::setupConnections()
	{
		connect(this, &PomodoroTimer::isPausedChanged, this, [this]()
		{
			if (m_isPaused)
			{
				m_timerEngine.stop();
				emit timerStopped();
			}
			else
			{
				m_timerEngine.start();
				emit timerStarted();
			}
		});

		connect(&m_timerEngine, &TimerEngine::timerTicked, [this](){emit timerTicked();});
		connect(&m_timerEngine, &TimerEngine::timerFinished, this, &PomodoroTimer::handleTimerEngineFinished);

		connect(&m_phaseManager, &PhaseManager::phaseChanged, &m_timerEngine, [this]
		{
			m_timerEngine.setStartTime(m_phaseManager.currentPhaseDuration());
			m_timerEngine.setTimeLeft(m_phaseManager.currentPhaseDuration());
			emit phaseChanged();
		});
	}


	PomodoroTimer::PomodoroTimer(
		const bool isPaused,
		const quint16 roundCount,
		const quint16 roundLength,
		const Phase phase,
		const std::chrono::seconds work,
		const std::chrono::seconds shortBreak,
		const std::chrono::seconds longBreak,
		QObject *parent
	)
		: QObject{ parent }
		  , m_isPaused{ isPaused }
		  , m_roundCount{ roundCount } ///TODO Добавить валидацию входных параметров в родительском классе
		  , m_roundLength{ roundLength }
		  , m_timerEngine{nullptr}
		  , m_phaseManager{ phase, work, shortBreak, longBreak }
	{
		m_timerEngine.setStartTime(m_phaseManager.currentPhaseDuration());
		m_timerEngine.setTimeLeft(m_phaseManager.currentPhaseDuration());
		setupConnections();
	}


	bool PomodoroTimer::isPaused() const
	{
		return m_isPaused;
	}


	quint16 PomodoroTimer::roundCount() const
	{
		return m_roundCount;
	}


	quint16 PomodoroTimer::roundLength() const
	{
		return m_roundLength;
	}


	Phase PomodoroTimer::currentPhase() const
	{
		return m_phaseManager.currentPhase();
	}


	auto PomodoroTimer::currentPhaseDuration() const -> std::chrono::seconds
	{
		return m_phaseManager.currentPhaseDuration();
	}


	auto PomodoroTimer::phaseDuration( const Phase phase ) const -> std::chrono::seconds
	{
		return m_phaseManager.phaseDuration(phase);
	}


	auto PomodoroTimer::timeLeft() const -> std::chrono::seconds
	{
		return m_timerEngine.timeLeft();
	}


	void PomodoroTimer::setIsPaused( const bool isPaused )
	{
		if (m_isPaused != isPaused)
		{
			m_isPaused = isPaused;
			emit isPausedChanged();
		}
	}


	void PomodoroTimer::setRoundCount(const quint16 roundCount)
	{
		if (m_roundCount != roundCount)
		{
			m_roundCount = roundCount;
			emit roundCountChanged();
		}
	}


	void PomodoroTimer::setRoundLength(const quint16 roundLength)
	{
		if (m_roundLength != roundLength)
		{
			m_roundLength = roundLength;
			emit roundLengthChanged();
		}
	}


	void PomodoroTimer::setCurrentPhase(const Phase phase)
	{
		if (m_phaseManager.currentPhase() != phase)
		{
			m_phaseManager.setCurrentPhase(phase);
			emit phaseChanged();
		}
	}


	void PomodoroTimer::setPhaseDuration( const Phase phase, const std::chrono::seconds phaseDuration )
	{
		m_phaseManager.setPhaseDuration(phase, phaseDuration);
	}


	void PomodoroTimer::start()
	{
		setIsPaused(false);
	}


	void PomodoroTimer::stop()
	{
		setIsPaused(true);
	}


	void PomodoroTimer::resetAndStop()
	{
		setIsPaused(false);
		m_timerEngine.setTimeLeft(m_phaseManager.currentPhaseDuration());

	}


	void PomodoroTimer::skipPhase()
	{
		if (m_phaseManager.currentPhase() == Phase::Work)
		{
			m_phaseManager.setCurrentPhase(Phase::ShortBreak);
		}
		else
		{
			m_phaseManager.setCurrentPhase(Phase::Work);
		}

		emit phaseChanged();
	}


	void PomodoroTimer::handleIsPausedChanged()
	{
		if (m_isPaused)
		{
			m_timerEngine.stop();
			emit timerStopped();
		}
		else
		{
			m_timerEngine.start();
			emit timerStarted();
		}
	}


	void PomodoroTimer::handleTimerEngineTicked()
	{
		emit timerTicked();
	}


	void PomodoroTimer::handleTimerEngineFinished()
	{
		if (m_phaseManager.currentPhase() != Phase::Work)
		{
			m_phaseManager.setCurrentPhase(Phase::Work);
		}
		else
		{
			if (m_roundCount == m_roundLength)
				m_phaseManager.setCurrentPhase(Phase::LongBreak);
			else
				m_phaseManager.setCurrentPhase(Phase::ShortBreak);

			++m_roundCount;
		}

		emit timerFinished();
	}
}
