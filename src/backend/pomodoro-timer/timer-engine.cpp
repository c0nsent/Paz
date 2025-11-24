#include "timer-engine.hpp"

namespace paz::backend::pt
{
	TimerEngine::TimerEngine( const qint16 totalDuration, const qint16 currentTime, QObject *parent )
		: QObject {parent}, m_currentTime{ currentTime }, m_totalDuration{ totalDuration }
	{
		m_timer.setInterval(1000);
		connect(&m_timer, &QTimer::timeout, this, &TimerEngine::handleTick);
	}


	qint16 TimerEngine::getTotalDuration() const { return m_totalDuration; }

	qint16 TimerEngine::getCurrentTime() const { return m_currentTime; }


	TimerEngine &TimerEngine::setDuration( const qint16 seconds )
	{
		m_totalDuration = seconds;
		return *this;
	}


	TimerEngine &TimerEngine::setCurrentTime( const qint16 seconds )
	{
		m_currentTime = seconds;
		return *this;
	}


	bool TimerEngine::isActive() const
	{
		return m_timer.isActive();
	}


	void TimerEngine::start()
	{
		m_timer.start();
	}


	void TimerEngine::start( const qint16 seconds )
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
