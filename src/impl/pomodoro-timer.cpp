/**
 * @date 12/4/25
 * 
 * @author amitayus_
 */

#include "pomodoro-timer.hpp"

#include <QtMinMax>

namespace impl
{
	PomodoroTimer::PomodoroTimer(QObject *parent)
		: QObject{parent}
		, m_state{State::Idle}
		, m_phase{Phase::Work}
		, m_phaseDurations{defaults::c_workDuration, defaults::c_shortBreakDuration, defaults::c_longBreakDuration}
		, m_sessionLength{defaults::c_sessionLength}
		, m_remainingTime{defaults::c_workDuration}
		, m_currentSessionCount{0}
	{
		m_timer.setTimerType(Qt::PreciseTimer);
		m_timer.setInterval(defaults::c_timerInterval);

		connect(&m_timer, &QTimer::timeout, this, &PomodoroTimer::updateRemainingTime);
	}

	bool PomodoroTimer::isActive() const {return m_timer.isActive();}

	PomodoroTimer::State PomodoroTimer::state() const {return m_state;}

	PomodoroTimer::Phase PomodoroTimer::phase() const {return m_phase;}

	quint16 PomodoroTimer::phaseDuration() const{ return m_phaseDurations[qToUnderlying(m_phase)]; }

	quint16 PomodoroTimer::phaseDuration(const Phase phase) const {return m_phaseDurations[qToUnderlying(phase)];}

	quint16 PomodoroTimer::sessionLength() const {return m_sessionLength;}

	quint16 PomodoroTimer::remainingTime() const {return m_remainingTime;}

	quint16 PomodoroTimer::currentSessionCount() const {return m_currentSessionCount;}


	void PomodoroTimer::start()
	{
		m_timer.start();

		m_state = State::Running;
		emit stateChanged(m_state);
	}


	void PomodoroTimer::start(const Phase phase)
	{
		m_phase = phase;
		emit phaseChanged(m_phase);

		m_remainingTime = phaseDuration();
		emit remainingTimeChanged(m_remainingTime);

		start();
	}


	void PomodoroTimer::start(const Phase phase, const quint16 seconds)
	{
		m_phase = phase;
		emit phaseChanged(m_phase);

		m_remainingTime = qMin(seconds, phaseDuration());
		emit remainingTimeChanged(m_remainingTime);

		start();
	}


	void PomodoroTimer::pause()
	{
		m_timer.stop();

		m_state = State::Paused;
		emit stateChanged(m_state);
	}


	void PomodoroTimer::reset()
	{
		m_timer.stop();

		m_remainingTime = phaseDuration();
		emit remainingTimeChanged(m_remainingTime);

		m_state = State::Idle;
		emit stateChanged(m_state);
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

		if (currentPhaseDuration != seconds) [[likely]]
		{
			currentPhaseDuration = seconds;
			emit phaseDurationChanged(seconds, phase);
		};

		if (m_phase == phase )
		{
			m_remainingTime = qMin(seconds, m_remainingTime );
			emit remainingTimeChanged(m_remainingTime);
		}
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
}
