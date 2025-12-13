/**
 * @date 12.12.2025
 * 
 * @author amitayus_
 */

#include "afk-timer.hpp"

#include "../core/constants.hpp"

namespace impl
{
	AfkTimer::AfkTimer(QObject *parent) : QObject{parent}
	{
		m_timer.setTimerType(Qt::CoarseTimer);
		m_timer.setInterval(defaults::c_timerInterval);

		connect(&m_timer, &QTimer::timeout, this, &AfkTimer::handleQTimerTimeout);
	}


	void AfkTimer::start(const quint16 seconds)
	{
		m_duration = m_remainingTime = seconds;

		m_timer.start();
		emit started(m_duration);
	}


	void AfkTimer::reset()
	{
		m_remainingTime = m_duration;

		m_timer.stop();
		emit finished();
	}


	void AfkTimer::handleQTimerTimeout()
	{
		if (m_remainingTime ==  c_timeIsOut) [[unlikely]] reset();

		emit ticked(--m_remainingTime);
	}
}