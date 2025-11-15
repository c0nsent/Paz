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

	quint16 PomodoroTimerBackend::getCurrentTime() const { return m_currentTime; }

	quint16 PomodoroTimerBackend::getCurrentCyclePomodoroCount() const { return m_currentCyclePomodoroCount; }

	PomodoroTimerBackend::State PomodoroTimerBackend::getState() const { return m_state; }


	PomodoroTimerBackend &PomodoroTimerBackend::setWorkTime( const quint16 workTime )
	{
		this->m_workTime = workTime;
		return *this;
	}

	PomodoroTimerBackend &PomodoroTimerBackend::setShortBreakTime( const quint16 shortBreakTime )
	{
		this->m_shortBreakTime = shortBreakTime;
	}

	PomodoroTimerBackend &PomodoroTimerBackend::setLongBreakTime( const quint16 longBreakTime )
	{
		this->m_longBreakTime = longBreakTime;
	}

	PomodoroTimerBackend &PomodoroTimerBackend::setPomodorosInCycle( const quint16 pomodorosInCycle )
	{
		this->m_pomodorosInCycle = pomodorosInCycle;
	}

	PomodoroTimerBackend &PomodoroTimerBackend::setCurrentTime( const quint16 currentTime )
	{
		this->m_currentTime = currentTime;
	}

	PomodoroTimerBackend &PomodoroTimerBackend::setCurrentCyclePomodoroCount(const quint16 currentCyclePomodoroCount )
	{
		this->m_currentCyclePomodoroCount = currentCyclePomodoroCount;
	}


	PomodoroTimerBackend &PomodoroTimerBackend::setState( const State state )
	{
		this->m_state = state;
	}


	PomodoroTimerBackend &PomodoroTimerBackend::start()
	{
		m_timer.start();
	}


	PomodoroTimerBackend &PomodoroTimerBackend::resume()
	{
		this->start();
	}


	PomodoroTimerBackend &PomodoroTimerBackend::stop()
	{
		this->m_timer.stop();
	}


	PomodoroTimerBackend &PomodoroTimerBackend::reset()
	{
		this->m_currentTime = 0;
		this->m_currentCyclePomodoroCount = 0;
		this->m_state = State::paused;
		this->m_timer.stop();
	}


	PomodoroTimerBackend &PomodoroTimerBackend::skip()
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
