/**
 * @date 11/27/25
 * 
 * @author amitayus_
 */

#include "phase-manager.hpp"

namespace paz::backend::pt
{
	PhaseManager::PhaseManager(
		const Phase phase,
		const qint16 workInSec,
		const qint16 shortBreakInSec,
		const qint16 longBreakInSec,
		QObject *parent
	)
		: QObject{parent}
		, m_currentPhase{phase}
		, m_arrPhaseDurations{workInSec, shortBreakInSec, longBreakInSec}
	{
	}


	Phase PhaseManager::currentPhase() const
	{
		return m_currentPhase;
	}

	qint16 PhaseManager::phaseDuration(const Phase rhs) const
	{
		return m_arrPhaseDurations[qToUnderlying(rhs)];
	}


	void PhaseManager::setCurrentPhase(const Phase phase)
	{
		//проверка делается только ради сигнала
		if (phase != m_currentPhase)
		{
			m_currentPhase = phase;
			emit phaseChanged();
		}
	}


	void PhaseManager::setPhaseDuration(const Phase phase, const qint16 phaseDuration)
	{
		auto &duration = m_arrPhaseDurations[qToUnderlying(phase)];

		if (phaseDuration == duration) return;

		duration = phaseDuration;
		emit phaseDurationChanged();

		switch(phase)
		{
			case Phase::Work:
				emit workDurationChanged();
				break;
			case Phase::ShortBreak:
				emit shortBreakDurationChanged();
				break;
			case Phase::LongBreak:
				emit longBreakDurationChanged();
				break;
		}
	}


	void PhaseManager::setPhaseDuration(const qint16 work, const qint16 shortBreak, const qint16 longBreak)
	{
		setPhaseDuration(Phase::Work, work);
		setPhaseDuration(Phase::ShortBreak, shortBreak);
		setPhaseDuration(Phase::LongBreak, longBreak);
	}
}
