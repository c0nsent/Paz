/**
 * @date 11/27/25
 * 
 * @author amitayus_
 */

#include "phase-manager.hpp"



namespace paz::impl::pt
{
	PhaseManager::PhaseManager(
		const Phase phase,
		const quint16 workInSec,
		const quint16 shortBreakInSec,
		const quint16 longBreakInSec,
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

	quint16 PhaseManager::phaseDuration(const Phase rhs) const
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


	void PhaseManager::setPhaseDuration(const Phase phase, const quint16 phaseDuration)
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


	void PhaseManager::setPhaseDuration(const quint16 work, const quint16 shortBreak, const quint16 longBreak)
	{
		setPhaseDuration(Phase::Work, work);
		setPhaseDuration(Phase::ShortBreak, shortBreak);
		setPhaseDuration(Phase::LongBreak, longBreak);
	}
}
