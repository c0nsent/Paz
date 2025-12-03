/**
 * @date 11/24/25
 * 
 * @author amitayus_
 */

#include "pomodoro-timer.hpp"

#include "../../core/constants.hpp"

#include <QDebug>

namespace paz::impl::pt
{
	void PomodoroTimer::setupSignalsReemitting()
	{
		connect(&m_timerEngine, &TimerEngine::timerTicked, [this](const std::chrono::seconds timeLeft)
	{
		emit ticked(timeLeft);
	});

		connect(&m_timerEngine, &TimerEngine::timerFinished, [this]{ emit timeout(); });

		connect(this, &PomodoroTimer::started, &m_timerEngine, [this]
		{
			emit started();
		});

		connect(this, &PomodoroTimer::stopped, &m_timerEngine, [this]
		{
			emit stopped();
		});

		connect(&m_phaseManager, &PhaseManager::phaseChanged, [this] (const Phase phase)
		{
			emit phaseChanged(phase);
		});

		connect(
			&m_phaseManager,
			&PhaseManager::phaseDurationChanged,
			[this] (const Phase phase, const std::chrono::seconds phaseDuration)
			{
				emit phaseDurationChanged(phase, phaseDuration);
			});
	}


	void PomodoroTimer::setupIntelConnections()
	{
		connect(this, &PomodoroTimer::started, [this] { m_active = true; });

		connect(this, &PomodoroTimer::stopped, [this] { m_active = false; });

		//connect(this, &PomodoroTimer::timerTicked, this, &PomodoroTimer::handleTimerTicked);
		connect(this, &PomodoroTimer::timeout, this, &PomodoroTimer::handleTimerFinished);
	}


	void PomodoroTimer::debugOutput() const
	{
		using std::chrono::seconds;

		connect(this, &PomodoroTimer::ticked, [] (const seconds timeLeft)
		{
			qDebug() << "Time left " << timeLeft.count();
		});

		connect(this, &PomodoroTimer::timeout, [this]
		{
			qDebug() << "Time is out. Нахуя на английском пишу?";
			qDebug() << "Оставшиеся время: " << timeLeft();
			qDebug() << "Current Phase" << currentPhase();
		});

		connect(this, &PomodoroTimer::started, [&]
		{
			qDebug() << "Start Timer";
			qDebug() << "Is Active:" << m_active;
			qDebug() << "Current Phase: " << currentPhase();
			qDebug() << "Phase Duration:" << currentPhaseDuration();
			qDebug() << "Timer Engine Start TIme: " << m_timerEngine.startTime();
		});

		connect(this, &PomodoroTimer::stopped, [&]
		{
			qDebug() << "Stop Timer";
			qDebug() << "Is Active:" << m_active;
			qDebug() << "Current Phase: " << currentPhase();
			qDebug() << "Phase Duration: " << currentPhaseDuration();
		});
	}


	PomodoroTimer::PomodoroTimer(
		const quint16 roundCount,
		const quint16 roundLength,
		const Phase phase,
		const std::chrono::seconds work,
		const std::chrono::seconds shortBreak,
		const std::chrono::seconds longBreak,
		QObject *parent
	)
		: QObject{ parent }
	, m_active{ false }
	, m_roundCount{ roundCount }
	, m_roundLength{ roundLength }
	, m_timerEngine{nullptr}
	, m_phaseManager{ phase, work, shortBreak, longBreak }
	{
		m_timerEngine.setNewTimer(currentPhaseDuration());

		setupSignalsReemitting();
		setupIntelConnections();

		if constexpr (c_debug) debugOutput();
	}


	bool PomodoroTimer::isActive() const
	{
		return m_active;
	}


	quint16 PomodoroTimer::roundCount() const
	{
		return m_roundCount;
	}


	quint16 PomodoroTimer::roundLength() const
	{
		return m_roundLength;
	}


	Phase PomodoroTimer::currentPhase() const
	{
		return m_phaseManager.currentPhase();
	}


	auto PomodoroTimer::currentPhaseDuration() const -> std::chrono::seconds
	{
		return m_phaseManager.currentPhaseDuration();
	}


	auto PomodoroTimer::phaseDuration(const Phase phase) const -> std::chrono::seconds
	{
		return m_phaseManager.phaseDuration(phase);
	}


	auto PomodoroTimer::timeLeft() const -> std::chrono::seconds
	{
		return m_timerEngine.timeLeft();
	}


	void PomodoroTimer::setRoundCount(const quint16 roundCount)
	{
		if (m_roundCount != roundCount)
		{
			m_roundCount = roundCount;
			emit roundCountChanged(m_roundCount);
		}
	}


	void PomodoroTimer::setRoundLength(const quint16 roundLength)
	{
		if (m_roundLength != roundLength)
		{
			m_roundLength = roundLength;
			emit roundLengthChanged(m_roundLength);
		}
	}


	void PomodoroTimer::setCurrentPhase(const Phase phase)
	{
		m_phaseManager.setCurrentPhase(phase);
	}


	void PomodoroTimer::setPhaseDuration(const Phase phase, const std::chrono::seconds phaseDuration)
	{
		m_phaseManager.setPhaseDuration(phase, phaseDuration);
	}


	void PomodoroTimer::start()
	{
		m_timerEngine.start();
	}


	void PomodoroTimer::stop()
	{
		m_timerEngine.stop();
	}

	void PomodoroTimer::resetAndStop()
	{
		m_timerEngine.resetAndStop();
	}


	void PomodoroTimer::skipPhase()
	{
		using enum Phase;

		const Phase next{ (currentPhase() == Work) ? ShortBreak : Work };
		setCurrentPhase(next);
	}


	void PomodoroTimer::handleTimerFinished()
	{
		using enum Phase;

		if (currentPhase() != Work)
		{
			setCurrentPhase(Work);
			return;
		}

		m_roundCount = (m_roundCount == m_roundLength) ? 0 : m_roundCount++;

		const Phase next{(m_roundCount == 0) ? ShortBreak : LongBreak};
		setCurrentPhase(next);

		m_timerEngine.setNewTimer(currentPhaseDuration());
	}
}