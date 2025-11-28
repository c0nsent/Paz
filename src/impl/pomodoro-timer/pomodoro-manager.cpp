/**
 * @date 11/24/25
 * 
 * @author amitayus_
 */

#include "pomodoro-manager.hpp"

namespace paz::impl::pt
{
	void PomodoroTimer::setupConnections()
	{
		connect(&m_timerEngine, &TimerEngine::timerTicked, [this](){emit timerTicked();});
		connect(&m_timerEngine, &TimerEngine::timerFinished, this, &PomodoroTimer::handleTimerEngineFinished);

		connect(&m_phaseManager, &PhaseManager::phaseChanged, &m_timerEngine, [this]
		{
			m_timerEngine.setStartTime(m_phaseManager.currentPhaseDuration());
			m_timerEngine.setTimeLeft(m_phaseManager.currentPhaseDuration());
		});
	}


	PomodoroTimer::PomodoroTimer(
		const bool isPaused,
		const quint16 roundCount,
		const quint16 roundLength,
		const quint16 inTotal,
		const quint16 startTime,
		const quint16 timeLeft,
		const Phase phase,
		const quint16 workInSec,
		const quint16 shortBreakInSec,
		const quint16 longBreakInSec,
		QObject *parent
	)
		: QObject{parent}
		  , m_isPaused{isPaused}
		  , m_roundCount{roundCount} ///TODO Добавить валидацию входных параметров в родительском классе
		  , m_roundLength{roundLength}
		  , m_inTotal{inTotal}
		  , m_timerEngine{startTime, timeLeft}
		  , m_phaseManager{phase, workInSec, shortBreakInSec, longBreakInSec}
	{
		setupConnections();
	}


	bool PomodoroTimer::isPaused() const { return m_isPaused; }

	quint16 PomodoroTimer::roundCount() const { return m_roundCount; }

	quint16 PomodoroTimer::roundLength() const { return m_roundLength; }

	quint16 PomodoroTimer::inTotal() const { return m_inTotal; }

	Phase PomodoroTimer::currentPhase() const { return m_phaseManager.currentPhase(); }

	quint16 PomodoroTimer::currentPhaseDuration() const { return m_phaseManager.currentPhaseDuration(); }

	quint16 PomodoroTimer::phaseDuration( const Phase phase ) const { return m_phaseManager.phaseDuration(phase); }

	quint16 PomodoroTimer::timeLeft() const { return m_timerEngine.timeLeft(); }


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


	void PomodoroTimer::setInTotal(const quint16 inTotal)
	{
		if (m_inTotal != inTotal)
		{
			m_inTotal = inTotal;
			emit inTotalChanged();
		}
	}


	void PomodoroTimer::setCurrentPhase(const Phase phase)
	{
		if (m_phaseManager.currentPhase() != phase)
		{

		}
	}


	void PomodoroTimer::setPhaseDuration( Phase phase, quint16 phaseDuration )
	{
	}


	void PomodoroTimer::setPhaseDuration( quint16 work, quint16 shortBreak, quint16 longBreak )
	{
	}


	void PomodoroTimer::start()
	{
		m_isPaused = false;
		emit timerStarted();
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
			++m_inTotal;
		}

		emit timerFinished();
	}


	/*void PomodoroManager::start( const quint16 startTime )
	{
		m_timerEngine.start(startTime);
	}*/


	void PomodoroTimer::stop()
	{
		m_isPaused = true;
		emit timerStopped();
	}


	void PomodoroTimer::resetAndStop()
	{
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
}
