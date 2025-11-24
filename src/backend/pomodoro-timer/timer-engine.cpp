#include "timer-engine.hpp"

namespace paz::backend::pt
{
	TimerEngine::TimerEngine( QObject *parent ) : QObject {parent}
	{
		m_timer.setInterval(1000);
		connect(&m_timer, &QTimer::timeout, this, &TimerEngine::handleTick);
	}


	quint16 TimerEngine::getTotalDuration() const { return m_totalDuration; }


	//quint16 TimerEngine::getCurrentTime() const { return m_currentTime; }


	TimerEngine &TimerEngine::setDuration( const quint16 seconds )
	{
		m_totalDuration = seconds;
		return *this;
	}


	/*TimerEngine &TimerEngine::setCurrentTime( const quint16 currentTime )
	{
		m_currentTime = currentTime;
		return *this;
	}*/


	bool TimerEngine::isActive() const
	{
		return m_timer.isActive();
	}


	void TimerEngine::start()
	{
		m_timer.start();
	}


	void TimerEngine::start( const quint16 seconds )
	{
		m_totalDuration = seconds;
		m_timer.start();
	}


	void TimerEngine::stop()
	{
		m_timer.stop();
	}


	void TimerEngine::resetAndStop()
	{
		m_currentTime = 0;
		m_timer.stop();
	}


	void TimerEngine::handleTick()
	{
		++m_currentTime;
		emit timerTicked();

		if (m_currentTime >= m_totalDuration)
		{
			this->resetAndStop();
			emit timerFinished();
		}
	}
}
