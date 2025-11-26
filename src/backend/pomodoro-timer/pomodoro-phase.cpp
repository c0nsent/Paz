/**
 * @date 11/16/25
 * 
 * @author amitayus_
 */

#include "pomodoro-phase.hpp"

namespace paz::backend::pt
{
	State::State(
		const bool isPaused ,
		const Phase phase,
		const qint16 workInSecs,
		const qint16 shortBreakInSecs,
		const qint16 longBreakInSecs,
		QObject *parent
		)
		: QObject{parent}
		, m_isPaused{isPaused}
		, m_currentPhase{phase}
		, m_phasesDuration{workInSecs, shortBreakInSecs, longBreakInSecs}
	{
	}


	bool State::isPaused() const { return m_isPaused; }

	State::Phase State::currentPhase() const { return m_currentPhase; }

	quint16 State::currentPhaseDuration() const { return m_phasesDuration[qToUnderlying(m_currentPhase)]; }

	quint16 State::phaseDuration(const Phase obj) const { return m_phasesDuration[qToUnderlying(obj)]; }


	void State::setIsPaused( const bool paused )
	{
		if (m_isPaused != paused) // Чет я сразу недопер что можно проверять изменен ли был проект с помощью сигнала
		{
			m_isPaused = paused;
			emit isPausedChanged();
		}
	}


	void State::setCurrentPhase(const Phase phase)
	{
		if (m_currentPhase != phase)
		{
			m_currentPhase = phase;
			emit phaseChanged();
		}
	}


	void State::setPhaseDuration( const Phase phase, const qint16 seconds )
	{
		auto &phaseDuration{m_phasesDuration[qToUnderlying(phase)]};

		if (seconds > 0 and phaseDuration != seconds)
		{
			phaseDuration = seconds;

			switch (phase)
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

			emit phaseDurationChanged();
		}
	}


	void State::setPhaseDuration( const qint16 work, const qint16 shortBreak, const qint16 longBreak )
	{
		setPhaseDuration(Phase::Work , work);
		setPhaseDuration(Phase::ShortBreak, shortBreak);
		setPhaseDuration(Phase::LongBreak, longBreak);
	}
}

