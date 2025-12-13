/**
 * @date 12/4/25
 * 
 * @author amitayus_
 */

#include "pomodoro-timer.hpp"

#include <QtMinMax>

namespace impl
{
	PomodoroTimer::PomodoroTimer(QObject *parent) : QObject{parent}
	{
		m_timer.setTimerType(Qt::PreciseTimer);
		m_timer.setInterval(defaults::c_timerInterval);

		connect(&m_timer, &QTimer::timeout, this, &PomodoroTimer::updateRemainingTime);
		connect(&m_afkTimer, &AfkTimer::finished, this, &PomodoroTimer::reset);
	}

	PomodoroTimer::State PomodoroTimer::state() const {return m_state;}

	PomodoroTimer::Phase PomodoroTimer::phase() const {return m_phase;}

	quint16 PomodoroTimer::phaseDuration() const{ return m_phaseDurations[qToUnderlying(m_phase)]; }

	quint16 PomodoroTimer::phaseDuration(const Phase phase) const {return m_phaseDurations[qToUnderlying(phase)];}

	quint16 PomodoroTimer::sessionLength() const {return m_sessionLength;}

	quint16 PomodoroTimer::remainingTime() const {return m_remainingTime;}

	quint16 PomodoroTimer::currentSessionCount() const {return m_currentSessionCount;}


	void PomodoroTimer::start()
	{
		if (trySetState(State::Running)) [[likely]] m_timer.start();
	}


	void PomodoroTimer::start(const Phase phase)
	{
		start(phase, phaseDuration());
	}


	void PomodoroTimer::start(const Phase phase, const quint16 seconds)
	{
		trySetPhase(phase);
		trySetRemainingTime(seconds);

		start();
	}


	void PomodoroTimer::pause()
	{
		if ( not trySetState(State::Paused)) [[unlikely]] return;

		if (m_phase == Phase::Work) m_afkTimer.start(3);

		m_timer.stop();
	}


	void PomodoroTimer::reset()
	{
		trySetState(State::Idle);
		trySetRemainingTime(phaseDuration());

		m_timer.stop();
	}


	void PomodoroTimer::toNextPhase()
	{
		using enum Phase;

		if (m_phase == ShortBreak or m_phase == LongBreak)
		{
			m_phase = Work;
			reset();
		}
		else
		{
			//Метод публичный, поэтому надо обрабатывать вышло ли время,
			//чтобы корректно помидорки считать
			if (m_remainingTime == c_timeIsOut) [[unlikely]]
			{
				m_currentSessionCount = (m_phase == LongBreak) ? 0 : ++m_currentSessionCount;
				emit pomodoroFinished(m_currentSessionCount);
			}

			m_phase = (m_currentSessionCount == m_sessionLength) ? LongBreak : ShortBreak;

			start(m_phase);
		}

		emit phaseChanged(m_phase);
	}


	void PomodoroTimer::setPhaseDuration(const quint16 seconds)
	{
		setPhaseDuration(seconds, m_phase);
	}


	void PomodoroTimer::setPhaseDuration(const quint16 seconds, const Phase phase)
	{
		auto &currentPhaseDuration{m_phaseDurations[qToUnderlying(phase)]};

		if (currentPhaseDuration == seconds) [[unlikely]] return;

		currentPhaseDuration = seconds;
		emit phaseDurationChanged(seconds, phase);

		if (m_phase == phase ) trySetRemainingTime(qMin(seconds, m_remainingTime));
	}


	void PomodoroTimer::setPhaseDuration(
		const quint16 workSec,
		const quint16 shortBreakSec,
		const quint16 longBreakSec
	)
	{
		setPhaseDuration(workSec, Phase::Work);
		setPhaseDuration(shortBreakSec, Phase::ShortBreak);
		setPhaseDuration(longBreakSec, Phase::LongBreak);
	}


	void PomodoroTimer::setSessionLength(const quint16 pomodoros)
	{
		if (m_sessionLength == pomodoros) [[unlikely]] return;

		m_sessionLength = pomodoros;
		emit sessionLengthChanged(pomodoros);
	}


	void PomodoroTimer::updateRemainingTime()
	{
		if (m_remainingTime == c_timeIsOut) [[unlikely]]
		{
			toNextPhase();
			return;
		}

		emit remainingTimeChanged(--m_remainingTime);
	}


	bool PomodoroTimer::trySetPhase(const Phase phase)
	{
		if (m_phase == phase) [[unlikely]]
			return false;

		m_phase = phase;
		emit phaseChanged(m_phase);

		return true;
	}


	bool PomodoroTimer::trySetRemainingTime(const quint16 remainingTime)
	{
		if (m_remainingTime == remainingTime) [[unlikely]]
			return false;

		m_remainingTime = remainingTime;
		emit remainingTimeChanged(m_remainingTime);

		return true;
	}


	bool PomodoroTimer::trySetState(const State state)
	{
		if (m_state == state) [[unlikely]]
			return false;

		m_state = state;
		emit stateChanged(m_state);

		return true;
	}
}
