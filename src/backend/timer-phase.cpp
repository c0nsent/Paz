/**
 * @date 11/16/25
 * 
 * @author amitayus_
 */

#include "timer-phase.hpp"

namespace paz::backend
{
	TimerPhase::TimerPhase( QObject *parent ) : QObject{parent}, m_phase{Phase::paused} {}


	TimerPhase::TimerPhase( const Phase phase, QObject *parent ) : QObject{parent}, m_phase{phase} {}


	TimerPhase::Phase TimerPhase::getPhase() const
	{
		return m_phase;
	}


	void TimerPhase::setPhase( const Phase phase )
	{
		m_phase = phase;
		emit phaseChanged();
	}
}

