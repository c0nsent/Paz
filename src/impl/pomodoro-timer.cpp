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
		, m_remainingTime{phaseDuration()}
		, m_currentSessionCount{0}
	{
		m_timer.setTimerType(Qt::PreciseTimer);
		m_timer.setInterval(defaults::c_timerInterval);

		connect(&m_timer, &QTimer::timeout, this, &PomodoroTimer::handleQTimerTimeout);
		connect(this, &PomodoroTimer::pomodoroFinished, [this] (const quint16)
		{
			m_currentSessionCount = (m_phase == Phase::LongBreak) ? 0 : ++m_currentSessionCount;
			start();
		});
		connect(this, &PomodoroTimer::timerStateChanged, [this] (const State state)
		{
			m_state = state;
		});
	}

	bool PomodoroTimer::isActive() const {return m_timer.isActive();}

	PomodoroTimer::State PomodoroTimer::state() const {return m_state;}

	PomodoroTimer::Phase PomodoroTimer::phase() const {return m_phase;}

	quint16 PomodoroTimer::phaseDuration() const{ return m_phaseDurations[qToUnderlying(m_phase)]; }

	quint16 PomodoroTimer::phaseDuration(const Phase phase) const {return m_phaseDurations[qToUnderlying(phase)];}

	quint16 PomodoroTimer::sessionLength() const {return m_sessionLength;}

	quint16 PomodoroTimer::currentSessionCount() const {return m_currentSessionCount;}

	quint16 PomodoroTimer::remainingTime() const {return m_remainingTime;}


	void PomodoroTimer::start()
	{
		m_timer.start();
		emit timerStateChanged(State::Running);
	}


	void PomodoroTimer::start(const quint16 seconds, const Phase phase)
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
		emit timerStateChanged(State::Paused);
	}


	void PomodoroTimer::reset()
	{
		m_remainingTime = phaseDuration();
		emit remainingTimeChanged(m_remainingTime);

		m_timer.stop();
		emit timerStateChanged(State::Idle);
	}


	void PomodoroTimer::toNextPhase()
	{
		using enum Phase;

		if (m_phase == Work)
		{
			//Метод публичный, поэтому надо обрабатывать вышло ли время,
			//чтобы корректно помидорки считать
			if (m_remainingTime == c_timeIsOut) [[unlikely]]
				emit pomodoroFinished(m_currentSessionCount);

			m_phase = (m_currentSessionCount == m_sessionLength) ? LongBreak : ShortBreak;
		}
		else
			m_phase = Work;

		emit phaseChanged(m_phase);

		reset();
	}


	void PomodoroTimer::setPhaseDuration(const Phase phase, const quint16 seconds)
	{
		auto &currentPhaseDuration{m_phaseDurations[qToUnderlying(phase)]};

		if (currentPhaseDuration != seconds) [[likely]]
		{
			currentPhaseDuration = seconds;
			emit phaseDurationChanged(phase, seconds);
		};

		if (m_phase == phase )
		{
			m_remainingTime = qMin(seconds, m_remainingTime );
			emit remainingTimeChanged(m_remainingTime);
		}
	}


	void PomodoroTimer::setAllPhaseDurations(
		const quint16 workSec,
		const quint16 shortBreakSec,
		const quint16 longBreakSec
	)
	{
		setPhaseDuration(Phase::Work, workSec);
		setPhaseDuration(Phase::ShortBreak, shortBreakSec);
		setPhaseDuration(Phase::LongBreak, longBreakSec);
	}


	void PomodoroTimer::setSessionLength(const quint16 pomodoros)
	{
		if (m_sessionLength == pomodoros) [[unlikely]] return;

		m_sessionLength = pomodoros;
		emit sessionLengthChanged(pomodoros);
	}


	void PomodoroTimer::handleQTimerTimeout()
	{
		if (m_remainingTime == c_timeIsOut) [[unlikely]]
			toNextPhase();
		else
		{
			--m_remainingTime;
			emit remainingTimeChanged(m_remainingTime);
		}
	}
}
