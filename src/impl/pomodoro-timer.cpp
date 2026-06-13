#include "pomodoro-timer.hpp"

#include <QMetaEnum>
#include <QString>
#include <QtMinMax>

namespace impl
{
    PomodoroTimer::PomodoroTimer(QObject *parent)
        : PomodoroTimer(CreateInfo{parent})
    {
    }

	PomodoroTimer::PomodoroTimer(const CreateInfo &data)
		: QObject{data.parent}
		  , m_state{data.state}
		  , m_phase{data.phase}
		  , m_phaseDurations{data.phaseDurations}
		  , m_sessionLength{data.sessionLength}
		  , m_remainingTime{data.phaseDurations.value(data.phase)}
		  , m_currentSessionCount{data.currentSessionCount}
	{
		m_timer.setTimerType(Qt::CoarseTimer);
		m_timer.setInterval(defaults::TIMER_INTERVAL);

		connect(&m_timer, &QTimer::timeout, this, &PomodoroTimer::updateRemainingTime);
	}


	PomodoroTimer::State PomodoroTimer::state() const {return m_state;}

	PomodoroTimer::Phase PomodoroTimer::phase() const {return m_phase;}

	u16 PomodoroTimer::phaseDuration() const{ return m_phaseDurations.value(m_phase); }

	u16 PomodoroTimer::phaseDuration(const Phase phase) const {return m_phaseDurations.value(phase);}

	u16 PomodoroTimer::sessionLength() const {return m_sessionLength;}

	u16 PomodoroTimer::remainingTime() const {return m_remainingTime;}

    QString PomodoroTimer::timeRemainingString() const
    {
	    return QString::asprintf("%02d:%02d", m_remainingTime / 60, m_remainingTime % 60);
    }

	u16 PomodoroTimer::currentSessionCount() const {return m_currentSessionCount;}

	void PomodoroTimer::start()
	{
		if (trySetState(State::Running)) [[likely]] m_timer.start();
	}


	void PomodoroTimer::start(const Phase phase)
	{
		start(phase, phaseDuration());
	}


	void PomodoroTimer::start(const Phase phase, const u16 seconds)
	{
		trySetPhase(phase);
		trySetRemainingTime(seconds);

		start();
	}


	void PomodoroTimer::pause()
	{
		if ( not trySetState(State::Paused)) [[unlikely]] return;

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


	void PomodoroTimer::setPhaseDuration(const u16 current)
	{
		setPhaseDuration({{m_phase, current}});
	}


	void PomodoroTimer::setPhaseDuration(const Phase phase, const u16 seconds)
	{
		setPhaseDuration({{phase, seconds}});
	}


	void PomodoroTimer::setPhaseDuration(const std::initializer_list<std::pair<Phase, u16>> &phaseDurations)
	{
		if (phaseDurations.size() > m_phaseDurations.size()) [[unlikely]]
				qWarning() << Q_FUNC_INFO << "\n" << "количество переданных параметров =  " << phaseDurations.size()
				<< "превосходит количество фаз" << m_phaseDurations.size();

		for (const auto &[phase, seconds] : phaseDurations)
		{
			if (m_phaseDurations.value(phase) == seconds) [[unlikely]] continue;

			m_phaseDurations.insert(phase, seconds);
			emit phaseDurationChanged(seconds, phase);

			if (m_phase == phase) [[unlikely]] trySetRemainingTime(qMin(seconds, m_remainingTime));
		}
	}


	void PomodoroTimer::setSessionLength(const u16 pomodoros)
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


	bool PomodoroTimer::trySetRemainingTime(const u16 remainingTime)
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


	QHash<PomodoroTimer::Phase, u16> PomodoroTimer::initializePhaseDurations()
	{
		const auto metaPhase{QMetaEnum::fromType<Phase>()};
		const auto enumSize{ metaPhase.keyCount() };

		QHash<Phase, u16> durations;
		durations.reserve(enumSize);

		for (auto i{0}; i != enumSize; ++i)
		{
			durations.emplace(static_cast<Phase>(i), defaults::PHASE_DURATIONS[i]);
		}

		return durations;
	}
}