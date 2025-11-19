#include "timer-engine.hpp"

namespace paz::backend
{
	TimerEngine::TimerEngine( QObject *parent ) : QObject {parent}
	{
		m_timer.setInterval(1000);
		connect(&m_timer, &QTimer::timeout, this, &TimerEngine::handleTick);
	}


	quint16 TimerEngine::getDuration() const { return m_duration; }


	quint16 TimerEngine::getCurrentTime() const { return m_currentTime; }


	TimerEngine &TimerEngine::setDuration( const quint16 duration )
	{
		m_duration = duration;
		return *this;
	}


	TimerEngine &TimerEngine::setCurrentTime( const quint16 currentTime )
	{
		m_currentTime = currentTime;
		return *this;
	}


	bool TimerEngine::isPaused() const
	{
		return not m_timer.isActive();
	}


	void TimerEngine::start()
	{
		m_timer.start();
	}


	void TimerEngine::pause()
	{
		m_timer.stop();
	}


	void TimerEngine::reset()
	{
		m_currentTime = 0;
	}


	void TimerEngine::handleTick()
	{
		++m_currentTime;
		emit timerTicked();

		if (m_currentTime >= m_duration)
			emit timerFinished();
	}
}
