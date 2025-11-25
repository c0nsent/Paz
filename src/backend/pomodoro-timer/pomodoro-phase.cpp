/**
 * @date 11/16/25
 * 
 * @author amitayus_
 */

#include "pomodoro-phase.hpp"

namespace paz::backend::pt
{
	PomodoroPhase::PomodoroPhase( const Phs phase,
		const qint16 workInSecs, const qint16 shortBreakInSecs, const qint16 longBreakInSecs, QObject *parent )
		: QObject{parent}, m_currentPhase{phase}, m_phasesDuration{ workInSecs, shortBreakInSecs, longBreakInSecs } {}


	PomodoroPhase::Phs PomodoroPhase::getCurrentPhase() const { return m_currentPhase; }

	quint16 PomodoroPhase::getCurrentPhaseDuration() const { return m_phasesDuration[qToUnderlying(m_currentPhase)]; }

	quint16 PomodoroPhase::getPhaseDuration( const Phs obj ) const { return m_phasesDuration[qToUnderlying(obj)]; }


	void PomodoroPhase::setCurrentPhase( const Phs phase )
	{
		if (m_currentPhase != phase) return;

		m_currentPhase = phase;
		emit phaseChanged();
	}


	void PomodoroPhase::setPhaseDuration( const Phs phase, const qint16 seconds )
	{
		auto &duration = m_phasesDuration[qToUnderlying(phase)];

		if (seconds < 0 or seconds == duration) return;

		duration = seconds;

		switch (phase)
		{
			case Phs::Work:
				emit workDurationChanged();
				break;
			case Phs::ShortBreak:
				emit shortBreakDurationChanged();
				break;
			case Phs::LongBreak:
				emit longBreakDurationChanged();
				break;
		}

		emit phaseDurationChanged();
	}


	void PomodoroPhase::setPhaseDuration( const qint16 work, const qint16 shortBreak, const qint16 longBreak )
	{
		setPhaseDuration(Phs::Work , work);
		setPhaseDuration(Phs::ShortBreak, shortBreak);
		setPhaseDuration(Phs::LongBreak, longBreak);
	}
}

