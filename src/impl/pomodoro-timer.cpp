/**
 * @date 12/4/25
 * 
 * @author amitayus_
 */

#include "pomodoro-timer.hpp"

#include <QMetaEnum>
#include <QtMinMax>

namespace impl
{
	struct PomodoroTimer::Initializer
	{
	private:

		const QMetaEnum metaPhase{QMetaEnum::fromType<Phase>()};

		[[nodiscard]] QHash<Phase, quint16> initializePhaseDurations() const;
	public:

		[[nodiscard]] quint16 remainingTime() const;

		QObject *parent{nullptr};

		State state{State::Idle};
		Phase phase{Phase::Work};

		QHash<Phase,quint16> phaseDurations{};

		quint16 sessionLength{defaults::c_sessionLength};
		quint16 currentSessionCount{0};
	};


	QHash<PomodoroTimer::Phase, quint16> PomodoroTimer::Initializer::initializePhaseDurations() const
	{
		QHash<Phase, quint16> durations;
		durations.reserve(this->metaPhase.keyCount());

		for (auto i{0}; i != this->metaPhase.keyCount(); ++i)
		{
			auto duration{defaults::c_phaseDurations.at(i)};

			if (not defaults::c_phaseDurations.contains(i))
			{
				duration = defaults::c_invalidPhaseDuration;
				qCritical() << "Default value for " << this->metaPhase.valueToKey(i) << "is not initialized";
			}

			durations.tryEmplace(static_cast<Phase>(i), duration);
		}

		return durations;
	}


	quint16 PomodoroTimer::Initializer::remainingTime() const
	{
		return this->phaseDurations.value(this->phase);
	}


	PomodoroTimer::PomodoroTimer(Initializer &&data)
		: QObject{data.parent}
		, m_state{data.state}
		, m_phase{data.phase}
		, m_phaseDurations{std::move(data.phaseDurations)}
		, m_sessionLength{data.sessionLength}
		, m_remainingTime{data.remainingTime()}
		, m_currentSessionCount{data.currentSessionCount}
	{
		m_timer.setTimerType(Qt::CoarseTimer);
		m_timer.setInterval(defaults::c_timerInterval);

		connect(&m_timer, &QTimer::timeout, this, &PomodoroTimer::updateRemainingTime);
	}


	PomodoroTimer::State PomodoroTimer::state() const {return m_state;}

	PomodoroTimer::Phase PomodoroTimer::phase() const {return m_phase;}

	quint16 PomodoroTimer::phaseDuration() const{ return m_phaseDurations.value(m_phase); }

	quint16 PomodoroTimer::phaseDuration(const Phase phase) const {return m_phaseDurations.value(phase);}

	quint16 PomodoroTimer::sessionLength() const {return m_sessionLength;}

	quint16 PomodoroTimer::remainingTime() const {return m_remainingTime;}

	quint16 PomodoroTimer::currentSessionCount() const {return m_currentSessionCount;}


	void PomodoroTimer::setPhaseDuration(PhaseDurations &&seconds) noexcept
	{
		setPhaseDuration(seconds.workDuration, Phase::Work);
		setPhaseDuration(seconds.shortBreakDuration, Phase::ShortBreak);
		setPhaseDuration(seconds.longBreakDuration, Phase::LongBreak);
	}


	void PomodoroTimer::start()
	{
		if (trySetState(State::Running)) [[likely]] m_timer.start();
	}


	void PomodoroTimer::start(const Phase phase)
	{
		start(phase, phaseDuration());
	}


	void PomodoroTimer::start(const Phase phase, const quint16 seconds)
	{
		trySetPhase(phase);
		trySetRemainingTime(seconds);

		start();
	}


	void PomodoroTimer::pause()
	{
		if ( not trySetState(State::Paused)) [[unlikely]] return;

		if (m_phase == Phase::Work) m_afkTimer.start(3);

		m_timer.stop();
	}


	void PomodoroTimer::reset()
	{
		trySetState(State::Idle);
		trySetRemainingTime(phaseDuration());

		m_timer.stop();
	}


	void PomodoroTimer::toNextPhase()
	{
		using enum Phase;

		if (m_phase == ShortBreak or m_phase == LongBreak)
		{
			m_phase = Work;
			reset();
		}
		else
		{
			//Метод публичный, поэтому надо обрабатывать вышло ли время,
			//чтобы корректно помидорки считать
			if (m_remainingTime == c_timeIsOut) [[unlikely]]
			{
				m_currentSessionCount = (m_phase == LongBreak) ? 0 : ++m_currentSessionCount;
				emit pomodoroFinished(m_currentSessionCount);
			}

			m_phase = (m_currentSessionCount == m_sessionLength) ? LongBreak : ShortBreak;

			start(m_phase);
		}

		emit phaseChanged(m_phase);
	}


	void PomodoroTimer::setPhaseDuration(const quint16 current)
	{
		setPhaseDuration(current, m_phase);
	}


	void PomodoroTimer::setPhaseDuration(const quint16 seconds, const Phase phase)
	{
		//Доделай эту чтобы по принципц if(tryAssign(phase)) emit хуйня
		auto &currentPhaseDuration{m_phaseDurations[qToUnderlying(phase)]};

		if (m_phaseDurations.tryInsert())
		if (m_phaseDurations.value(phase) == seconds) [[unlikely]] return;

		currentPhaseDuration = seconds;
		emit phaseDurationChanged(seconds, phase);

		if (m_phase == phase) trySetRemainingTime(qMin(seconds, m_remainingTime));
	}


	void PomodoroTimer::setSessionLength(const quint16 pomodoros)
	{
		if (m_sessionLength == pomodoros) [[unlikely]] return;

		m_sessionLength = pomodoros;
		emit sessionLengthChanged(pomodoros);
	}


	void PomodoroTimer::updateRemainingTime()
	{
		if (m_remainingTime != c_timeIsOut) [[likely]]
			emit remainingTimeChanged(--m_remainingTime);
		else
			toNextPhase();
	}


	bool PomodoroTimer::trySetPhase(const Phase phase)
	{
		if (m_phase == phase) [[unlikely]] return false;

		m_phase = phase;
		emit phaseChanged(m_phase);

		return true;
	}


	bool PomodoroTimer::trySetRemainingTime(const quint16 remainingTime)
	{
		if (m_remainingTime == remainingTime) [[unlikely]] return false;

		m_remainingTime = remainingTime;
		emit remainingTimeChanged(m_remainingTime);

		return true;
	}


	bool PomodoroTimer::trySetState(const State state)
	{
		if (m_state == state) [[unlikely]] return false;

		m_state = state;
		emit stateChanged(m_state);

		return true;
	}
}
