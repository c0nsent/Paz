/**
* @date 11/14/25
 *
 * @author amitayus_
 */

#include "timer-engine.hpp"

#include "../../core/constants.hpp"

#include <algorithm>


namespace paz::impl::pt
{
	using namespace std::literals::chrono_literals;
	TimerEngine::TimerEngine(QObject *parent)
	: TimerEngine{0s, 0s, parent}
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
			emit timeLeftChanged(m_timeLeft);
		}

		m_timer.setTimerType(Qt::PreciseTimer); ///Я ебал аллайнмент в 5% у CoarseTimer
		m_timer.setInterval({defaults::c_TimerInterval});

		connect(&m_timer, &QTimer::timeout, this, &TimerEngine::handleTick);
		connect(this, &TimerEngine::startTimeChanged, this, &TimerEngine::setTimeLeft);
	}


	auto TimerEngine::startTime() const -> std::chrono::seconds { return m_startTime; }

	auto TimerEngine::timeLeft() const -> std::chrono::seconds { return m_timeLeft; }

	bool TimerEngine::isActive() const { return m_timer.isActive(); }


	void TimerEngine::setStartTime(const std::chrono::seconds duration)
	{
		if (m_startTime == duration) return;

		m_startTime = duration;
		emit startTimeChanged(m_startTime);
	}


	void TimerEngine::setTimeLeft(const std::chrono::seconds duration)
	{
		if (m_timeLeft == duration) return;

		m_timeLeft = std::min(m_timeLeft, duration);
		emit timeLeftChanged(m_timeLeft);
	}


	void TimerEngine::setNewTimer(const std::chrono::seconds duration)
	{
		if (m_startTime != duration)
		{
			m_startTime = duration;
			emit startTimeChanged(duration);
		}

		if (m_timeLeft != duration)
		{
			m_timeLeft = duration;
			emit timeLeftChanged(duration);
		}
	}


	void TimerEngine::start()
	{
		m_timer.start();
		emit timerStarted();
	}


	void TimerEngine::stop()
	{
		m_timer.stop();
		emit timerStopped();
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
		emit timerTicked(m_timeLeft);
	}
}
