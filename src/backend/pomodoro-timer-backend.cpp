/**
 * @date 11/14/25
 * 
 * @author amitayus_
 */

#include "pomodoro-timer-backend.hpp"

namespace paz::backend
{
	PomodoroTimerBackend::PomodoroTimerBackend( const quint16 workTime, const quint16 shortBreakTime,
		const quint16 longBreakTime, const quint16 pomodorosInCycle, QObject *parent )
	: QObject{parent}, m_workTime{workTime}, m_shortBreakTime{shortBreakTime}
	, m_longBreakTime{longBreakTime}, m_pomodorosInCycle{pomodorosInCycle}
	{
		m_timer.setInterval(1000);

		QObject::connect(&m_timer, &QTimer::timeout, this, &PomodoroTimerBackend::timerTicked);
	}


	quint16 PomodoroTimerBackend::getWorkTime() const { return m_workTime; }


	quint16 PomodoroTimerBackend::getShortBreakTime() const { return m_shortBreakTime; }


	quint16 PomodoroTimerBackend::getLongBreakTime() const { return m_longBreakTime; }


	quint16 PomodoroTimerBackend::getPomodorosInCycle() const { return m_pomodorosInCycle; }


	quint16 PomodoroTimerBackend::getCurrentCyclePomodoroCount() const { return m_currentCyclePomodoroCount; }


	void PomodoroTimerBackend::setPomodorosInCycle( const quint16 pomodorosInCycle )
	{
		this->m_pomodorosInCycle = pomodorosInCycle;
	}


	void PomodoroTimerBackend::setCurrentCyclePomodoroCount(const quint16 currentCyclePomodoroCount )
	{
		this->m_currentCyclePomodoroCount = currentCyclePomodoroCount;
	}


	PomodoroTimerBackend::State PomodoroTimerBackend::getState() const { return m_state; }


	quint16 PomodoroTimerBackend::getCurrentTime() const
	{
	}


	void PomodoroTimerBackend::setWorkTime( quint16 workTime )
	{
	}


	void PomodoroTimerBackend::setShortBreakTime( quint16 shortBreakTime )
	{
	}


	void PomodoroTimerBackend::setLongBreakTime( quint16 longBreakTime )
	{
	}


	void PomodoroTimerBackend::setState( State state )
	{
	}


	void PomodoroTimerBackend::setCurrentTime( quint16 currentTime )
	{
	}


	void PomodoroTimerBackend::start()
	{
	}


	void PomodoroTimerBackend::stop()
	{
	}


	void PomodoroTimerBackend::resume()
	{
	}


	void PomodoroTimerBackend::pause()
	{
	}


	void PomodoroTimerBackend::reset()
	{
	}


	void PomodoroTimerBackend::timerTicked()
	{
		if (m_state == State::paused) return;

		m_currentTime++;

		if (m_state == State::work and m_currentTime >= m_workTime)
		{
			if (m_currentCyclePomodoroCount < m_pomodorosInCycle)
			{
				m_currentCyclePomodoroCount++;
				m_state = State::shortBreak;
			}
			else
			{
				m_currentCyclePomodoroCount = 0;
				m_state = State::longBreak;
			}

			emit timerFinished();
		}
		else if (m_currentTime >= m_shortBreakTime or m_currentTime >= m_longBreakTime)
		{
			m_state = State::work;

			emit timerFinished();
		}
	}


	void PomodoroTimerBackend::timerFinished()
	{
		m_currentTime = 0;
	}

}
