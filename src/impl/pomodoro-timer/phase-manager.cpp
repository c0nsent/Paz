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
		const std::chrono::seconds work,
		const std::chrono::seconds shortBreak,
		const std::chrono::seconds longBreak,
		QObject *parent
	)
		: QObject{parent}
		, m_currentPhase{phase}
		, m_arrPhaseDurations{work, shortBreak, longBreak}
	{
	}


	Phase PhaseManager::currentPhase() const
	{
		return m_currentPhase;
	}


	auto PhaseManager::currentPhaseDuration() const -> std::chrono::seconds
	{
		return phaseDuration(m_currentPhase);
	}


	auto PhaseManager::phaseDuration(const Phase phase) const -> std::chrono::seconds
	{
		return m_arrPhaseDurations[qToUnderlying(phase)];
	}


	void PhaseManager::setCurrentPhase(const Phase phase)
	{
		if (phase == m_currentPhase) return;

		m_currentPhase = phase;
		emit phaseChanged(phase);
	}


	void PhaseManager::setPhaseDuration(const Phase phase, const std::chrono::seconds phaseDuration)
	{
		auto &duration = m_arrPhaseDurations[qToUnderlying(phase)];

		if (phaseDuration == duration) return;

		duration = phaseDuration;
		emit phaseDurationChanged(phase, phaseDuration);
	}
}
