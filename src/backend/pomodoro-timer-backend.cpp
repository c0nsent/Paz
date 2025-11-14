/**
 * @date 11/14/25
 * 
 * @author amitayus_
 */

#include "pomodoro-timer-backend.hpp"


paz::backend::PomodoroTImerBackend::PomodoroTImerBackend( const quint16 workTime, const quint16 shortBreakTime, const quint16 longBreakTime, QObject *parent )
	: QObject{parent}, m_workTime{workTime}, m_shortBreakTime{shortBreakTime}, m_longBreakTime{longBreakTime}, m_currentTime{0}, m_state{State::paused}
{
	m_timer.setInterval(1000);

	QObject::connect(&m_timer, &QTimer::timeout, this, &PomodoroTImerBackend::timerTicked);

}


quint16 paz::backend::PomodoroTImerBackend::getWorkTime() const
{
}


quint16 paz::backend::PomodoroTImerBackend::getShortBreakTime() const
{
}


quint16 paz::backend::PomodoroTImerBackend::getLongBreakTime() const
{
}


paz::backend::PomodoroTImerBackend::State paz::backend::PomodoroTImerBackend::getState() const
{
}


quint16 paz::backend::PomodoroTImerBackend::getCurrentTime() const
{
}


void paz::backend::PomodoroTImerBackend::setWorkTime( quint16 workTime )
{
}


void paz::backend::PomodoroTImerBackend::setShortBreakTime( quint16 shortBreakTime )
{
}


void paz::backend::PomodoroTImerBackend::setLongBreakTime( quint16 longBreakTime )
{
}


void paz::backend::PomodoroTImerBackend::setState( State state )
{
}


void paz::backend::PomodoroTImerBackend::setCurrentTime( quint16 currentTime )
{
}


void paz::backend::PomodoroTImerBackend::start()
{
}


void paz::backend::PomodoroTImerBackend::stop()
{
}


void paz::backend::PomodoroTImerBackend::resume()
{
}


void paz::backend::PomodoroTImerBackend::pause()
{
}


void paz::backend::PomodoroTImerBackend::reset()
{
}


void paz::backend::PomodoroTImerBackend::timerTicked()
{
	m_currentTime++;

	switch (m_state)
	{
		case State::work:
			if (m_currentTime == m_workTime)
			{
				m_currentTime = 0;
				m_state = State::shortBreak;
			}
			break;
		case State::shortBreak:
			if (m_currentTime == m_shortBreakTime)
			{
				m_currentTime = 0;
				m_state
			}

	}

}


void paz::backend::PomodoroTImerBackend::timerFinished() const
{
}
