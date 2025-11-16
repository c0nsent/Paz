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

		QObject::connect(&m_timer, &QTimer::timeout, this, &PomodoroTimerBackend::handleTimerTick);

	}


	quint16 PomodoroTimerBackend::getWorkTime() const { return m_workTime; }


	quint16 PomodoroTimerBackend::getShortBreakTime() const { return m_shortBreakTime; }


	quint16 PomodoroTimerBackend::getLongBreakTime() const { return m_longBreakTime; }

	quint16 PomodoroTimerBackend::getPomodorosInCycle() const { return m_pomodorosInCycle; }

	quint16 PomodoroTimerBackend::getCurrentTime() const { return m_currentTime; }

	quint16 PomodoroTimerBackend::getCurrentCyclePomodoroCount() const { return m_currentCyclePomodoroCount; }

	PomodoroTimerBackend::Phase PomodoroTimerBackend::getState() const { return m_phase; }


	PomodoroTimerBackend &PomodoroTimerBackend::setWorkTime( const quint16 workTime )
	{
		this->m_workTime = workTime;
		return *this;
	}

	PomodoroTimerBackend &PomodoroTimerBackend::setShortBreakTime( const quint16 shortBreakTime )
	{
		this->m_shortBreakTime = shortBreakTime;
		return *this;
	}

	PomodoroTimerBackend &PomodoroTimerBackend::setLongBreakTime( const quint16 longBreakTime )
	{
		this->m_longBreakTime = longBreakTime;
		return *this;
	}

	PomodoroTimerBackend &PomodoroTimerBackend::setPomodorosInCycle( const quint16 pomodorosInCycle )
	{
		this->m_pomodorosInCycle = pomodorosInCycle;
		return *this;
	}

	PomodoroTimerBackend &PomodoroTimerBackend::setCurrentTime( const quint16 currentTime )
	{
		this->m_currentTime = currentTime;
		return *this;
	}

	PomodoroTimerBackend &PomodoroTimerBackend::setCurrentCyclePomodoroCount(const quint16 currentCyclePomodoroCount )
	{
		this->m_currentCyclePomodoroCount = currentCyclePomodoroCount;
		return *this;
	}


	PomodoroTimerBackend &PomodoroTimerBackend::setState( const Phase state )
	{
		this->m_phase = state;
		return *this;
	}


	void PomodoroTimerBackend::start()
	{
		m_timer.start();
	}


	void PomodoroTimerBackend::stop()
	{
		this->m_timer.stop();
	}


	void PomodoroTimerBackend::reset()
	{
		this->m_currentTime = 0;
		this->m_currentCyclePomodoroCount = 0;
		this->m_phase = Phase::paused;
		this->m_timer.stop();
	}


	void PomodoroTimerBackend::skipCurrentPhase()
	{

	}


	void PomodoroTimerBackend::handleTimerTick()
	{
		m_currentTime++;

		if (m_phase == Phase::work and m_currentTime >= m_workTime)


		emit timerTicked();
	}


	void PomodoroTimerBackend::handlePhaseChange()
	{
	}


	void PomodoroTimerBackend::timerTicked()
	{
		if (m_phase == Phase::paused)
			return;

		m_currentTime++;

		if (m_phase == Phase::work and m_currentTime >= m_workTime)
		{
			if (m_currentCyclePomodoroCount < m_pomodorosInCycle)
			{
				m_currentCyclePomodoroCount++;
				m_phase = Phase::shortBreak;
			}
			else
			{
				m_currentCyclePomodoroCount = 0;
				m_phase = Phase::longBreak;
			}

			emit phaseChanged();
		}
		else if (m_currentTime >= m_shortBreakTime or m_currentTime >= m_longBreakTime)
		{
			m_phase = Phase::work;

			emit phaseChanged();
		}

	}


	void PomodoroTimerBackend::phaseChanged()
	{
	}

}
