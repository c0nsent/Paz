/**
* @date 11/14/25
 *
 * @author amitayus_
 */

#include "timer-engine.hpp"

#include "../core/constants.hpp"


namespace paz::impl::pt
{
	TimerEngine::TimerEngine( QObject *parent )
	: TimerEngine{defaults::c_workDuration, defaults::c_workDuration}
	{
	}


	TimerEngine::TimerEngine(const std::chrono::seconds startTime, QObject *parent)
		: TimerEngine{startTime, startTime, parent}
	{
	}
	TimerEngine::TimerEngine(const std::chrono::seconds startTime, const std::chrono::seconds timeLeft, QObject *parent)
		: QObject {parent}, m_startTime{startTime}, m_timeLeft{timeLeft}
	{
		if (m_timeLeft > m_startTime)
		{
			m_timeLeft = m_startTime;
			emit timeExceeded();
			emit timeLeftChanged();
		}

		m_timer.setTimerType(Qt::PreciseTimer); ///Я ебал аллайнмент в 5% у CoarseTimer
		m_timer.setInterval({defaults::c_TimerInterval});
		connect(&m_timer, &QTimer::timeout, this, &TimerEngine::handleTick);
	}


	auto TimerEngine::startTime() const -> std::chrono::seconds { return m_startTime; }

	auto TimerEngine::timeLeft() const -> std::chrono::seconds { return m_timeLeft; }

	bool TimerEngine::isActive() const { return m_timer.isActive(); }


	void TimerEngine::setStartTime( const std::chrono::seconds duration )
	{
		if (m_startTime != duration)
		{
			m_startTime = duration;
			emit startTimeChanged();
		};

		if (m_startTime < m_timeLeft)
		{
			m_timeLeft = m_startTime;
			emit timeExceeded();
			emit timeLeftChanged();
		}
	}


	void TimerEngine::setTimeLeft(const std::chrono::seconds duration)
	{
		if (m_timeLeft != duration)
		{
			m_timeLeft = duration;
			emit timeLeftChanged();
		}
	}


	void TimerEngine::start()
	{
		m_timer.start();
	}


	/*
	void TimerEngine::start( const std::chrono::seconds seconds )
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
		if (m_timeLeft == std::chrono::seconds::zero())
		{
			this->resetAndStop();
			emit timerFinished();
			return;
		}

		--m_timeLeft; //Перенес вниз, потому иначе был бы underflow при m_timeLeft = 0
		emit timerTicked();
	}
}
