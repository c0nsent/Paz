/**
 * @date 11/16/25
 * 
 * @author amitayus_
 */

#include "pomodoro-phase.hpp"

namespace paz::backend::pt
{
	qint16 PomodoroPhase::toQint16( Phs phase ) { return static_cast<qint16>(phase); }


	PomodoroPhase::PomodoroPhase( const Phs phase,
		const qint16 work, const qint16 shortBreak, const qint16 longBreak, QObject *parent )
		: QObject{parent}, m_currentPhase{phase}, m_phasesDuration{ work, shortBreak, longBreak } {}


	PomodoroPhase::Phs PomodoroPhase::getCurrentPhase() const { return m_currentPhase; }

	quint16 PomodoroPhase::getCurrentPhaseDuration() const { return m_phasesDuration[toQint16(m_currentPhase)]; }

	quint16 PomodoroPhase::getPhaseDuration( const Phs obj ) const { return m_phasesDuration[toQint16(obj)]; }


	void PomodoroPhase::setCurrentPhase( const Phs phase )
	{
		m_currentPhase = phase;
		emit phaseChanged();
	}


	void PomodoroPhase::setPhaseDuration( const Phs phase, const qint16 seconds )
	{
		m_phasesDuration[toQint16(phase)] = seconds;
		emit phaseDurationChanged();
	}


	void PomodoroPhase::setPhaseDuration( const qint16 work, const qint16 shortBreak, const qint16 longBreak )
	{
		m_phasesDuration[toQint16( Phs::work )] = work;
		m_phasesDuration[toQint16( Phs::shortBreak )] = shortBreak;
		m_phasesDuration[toQint16( Phs::longBreak )] = longBreak;

		emit phaseDurationChanged();
	}
}

