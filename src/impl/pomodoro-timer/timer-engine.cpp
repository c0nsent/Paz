/**
* @date 11/14/25
 *
 * @author amitayus_
 */

#include "timer-engine.hpp"


namespace paz::impl::pt
{
	TimerEngine::TimerEngine(const quint16 startTime, QObject *parent)
		: TimerEngine{startTime, startTime, parent}
	{
	}
	TimerEngine::TimerEngine(const quint16 startTime, const quint16 timeLeft, QObject *parent)
		: QObject {parent}, m_startTime{startTime}, m_timeLeft{timeLeft}
	{
		if (m_timeLeft > m_startTime)
		{
			m_timeLeft = m_startTime;
			emit timeExceeded();
			emit timeLeftChanged();
		}

		m_timer.setTimerType(Qt::PreciseTimer); ///Я ебал аллайнмент в 5% у CoarseTimer
		m_timer.setInterval(1000);
		connect(&m_timer, &QTimer::timeout, this, &TimerEngine::handleTick);
	}


	quint16 TimerEngine::startTime() const { return m_startTime; }

	quint16 TimerEngine::timeLeft() const { return m_timeLeft; }

	bool TimerEngine::isActive() const { return m_timer.isActive(); }


	TimerEngine &TimerEngine::setStartTime(const quint16 seconds)
	{
		if (m_startTime != seconds)
		{
			m_startTime = seconds;
			emit startTimeChanged();
		};

		if (m_startTime < m_timeLeft)
		{
			m_timeLeft = m_startTime;
			emit timeExceeded();
			emit timeLeftChanged();
		}

		return *this;
	}


	TimerEngine &TimerEngine::setTimeLeft(const quint16 seconds)
	{
		if (m_timeLeft != seconds)
		{
			m_timeLeft = seconds;
			emit timeLeftChanged();
		}

		return *this;
	}


	void TimerEngine::start()
	{
		m_timer.start();
	}


	/*
	void TimerEngine::start( const quint16 seconds )
	{
		setStartTime(seconds);
		setTimeLeft(seconds);
		m_timer.start();
	}
	*/


	void TimerEngine::stop()
	{
		m_timer.stop();
	}


	void TimerEngine::resetAndStop()
	{
		setTimeLeft(m_startTime);
		m_timer.stop();
	}


	void TimerEngine::handleTick()
	{
		if (m_timeLeft == 0)
		{
			this->resetAndStop();
			emit timerFinished();
			return;
		}

		--m_timeLeft; //Перенес вниз, потому иначе был бы underflow при m_timeLeft = 0
		emit timerTicked();
	}
}
