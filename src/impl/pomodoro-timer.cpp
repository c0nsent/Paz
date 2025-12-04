/**
 * @date 12/4/25
 * 
 * @author amitayus_
 */

#include "pomodoro-timer.hpp"

#include <QtMinMax>

namespace paz::impl
{
	PomodoroTimer::PomodoroTimer(QObject *parent)
		: QObject{parent}
		, m_currentPhase{Phase::Work}
		, m_phaseDurations{defaults::c_workDuration, defaults::c_shortBreakDuration, defaults::c_longBreakDuration}
		, m_sessionLength{6}
		, m_remainingTime{m_phaseDurations[qToUnderlying(m_currentPhase)]}
		, m_currentSessionCount{0}
	{
		m_timer.setTimerType(Qt::PreciseTimer);
		m_timer.setInterval(defaults::c_TimerInterval);

		connect(&m_timer, &QTimer::timeout, this, &PomodoroTimer::handleQTimerTimeout);
	}


	PomodoroTimer::PomodoroTimer(
		const Phase currentPhase,
		const std::chrono::seconds workPhase,
		const std::chrono::seconds shortBreakPhase,
		const std::chrono::seconds longBreakPhase,
		const qint64 sessionLength,
		QObject *parent
	)
		: QObject{parent}
		, m_currentPhase{currentPhase}
		, m_phaseDurations{ workPhase, shortBreakPhase, longBreakPhase }
		, m_sessionLength{sessionLength}
		, m_remainingTime{m_phaseDurations[qToUnderlying(m_currentPhase)]}
		, m_currentSessionCount{0}
	{
		m_timer.setTimerType(Qt::PreciseTimer);
		m_timer.setInterval(defaults::c_TimerInterval);

		connect(&m_timer, &QTimer::timeout, this, &PomodoroTimer::handleQTimerTimeout);
	}


	bool PomodoroTimer::isActive() const {return m_timer.isActive();}


	void PomodoroTimer::start()
	{
		m_timer.start();
		emit started();
	}


	void PomodoroTimer::start(const std::chrono::seconds duration)
	{
		m_remainingTime = qMin(duration, m_phaseDurations[qToUnderlying(m_currentPhase)]);
		emit remainingTimeChanged(m_remainingTime);
		start();
	}


	void PomodoroTimer::pause()
	{
		m_timer.stop();
		emit paused();
	}


	void PomodoroTimer::reset()
	{
		m_remainingTime = m_phaseDurations[qToUnderlying(m_currentPhase)];
		emit remainingTimeChanged(m_remainingTime);
		pause();
	}


	void PomodoroTimer::toNextPhase()
	{
		using enum Phase;

		if (m_currentPhase == Work)
			m_currentPhase = (m_currentSessionCount == m_sessionLength) ? LongBreak : ShortBreak;
		else
			m_currentPhase = Work;

		emit phaseChanged(m_currentPhase);
	}


	void PomodoroTimer::setPhaseDuration(const Phase phase, const std::chrono::seconds duration)
	{
		auto &currentPhaseDuration{m_phaseDurations[qToUnderlying(phase)]};

		if (currentPhaseDuration != duration)
		{
			currentPhaseDuration = duration;
			emit phaseDurationChanged(phase, duration);
		};

		if (m_currentPhase == phase )
		{
			m_remainingTime = qMin(duration, m_remainingTime );
			emit remainingTimeChanged(m_remainingTime);
		}
	}


	void PomodoroTimer::setSessionLength(const qint64 pomodoros)
	{
		if (m_sessionLength == pomodoros) return;

		m_sessionLength = pomodoros;
		emit sessionLengthChanged(pomodoros);
	}


	void PomodoroTimer::handleQTimerTimeout()
	{
		if (m_remainingTime != std::chrono::seconds::zero())
		{
			--m_remainingTime;
			emit remainingTimeChanged(m_remainingTime);
			return;
		}

		toNextPhase();
		m_remainingTime = m_phaseDurations[qToUnderlying(m_currentPhase)];
		emit remainingTimeChanged(m_remainingTime);

		m_currentSessionCount = (m_currentPhase == Phase::LongBreak) ? 0 : ++m_currentSessionCount;
		emit pomodoroFinished(m_currentSessionCount);

		reset();
		emit finished();
	}
}
