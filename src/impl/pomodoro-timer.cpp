#include "pomodoro-timer.hpp"

#include <QMetaEnum>
#include <QString>


namespace impl
{
    PomodoroTimer::PomodoroTimer(QObject *parent) : PomodoroTimer(CreateInfo{parent}) {}


	PomodoroTimer::PomodoroTimer(const CreateInfo &data)
		: QObject{data.parent}
        , m_workDuration{data.workPhaseDuration}
        , m_shortBreakDuration{data.shortBreakDuration}
        , m_longBreakDuration{data.workPhaseDuration}
        , m_sessionLength{data.sessionLength}
        , m_state{State::Idle}
        , m_phase{Phase::Work}
        , m_remainingTime{phaseDuration()}
        , m_currentSessionCount{0}
    {
	    m_timer.setTimerType(Qt::CoarseTimer);
    	m_timer.setInterval(defaults::TIMER_INTERVAL);

    	connect(&m_timer, &QTimer::timeout, this, &PomodoroTimer::tick);
    	connect(this, &PomodoroTimer::phaseDurationChanged, this, &PomodoroTimer::updateRemainingTime);
    }

	PomodoroTimer::State PomodoroTimer::state() const {return m_state;}

	PomodoroTimer::Phase PomodoroTimer::phase() const {return m_phase;}

    u16 PomodoroTimer::phaseDuration() const
    {
        return phaseDuration(m_phase);
    }

	u16 PomodoroTimer::phaseDuration(const Phase phase) const
    {
        switch (phase)
        {
            case Phase::Work: return m_workDuration;
            case Phase::ShortBreak: return m_shortBreakDuration;
            case Phase::LongBreak: return m_longBreakDuration;
        }

        return 0;
    }

	u16 PomodoroTimer::workDuration() const
	{
    	return m_workDuration;
	}

	u16 PomodoroTimer::shortBreakDuration() const
	{
    	return m_shortBreakDuration;
	}

	u16 PomodoroTimer::longBreakDuration() const
	{
    	return m_longBreakDuration;
	}

	void PomodoroTimer::setWorkDuration(u16 seconds)
	{
    	setPhaseDuration(Phase::Work, seconds);
	}

	void PomodoroTimer::setShortBreakDuration(u16 seconds)
	{
    	setPhaseDuration(Phase::ShortBreak, seconds);
	}

	void PomodoroTimer::setLongBreakDuration(u16 seconds)
	{
    	setPhaseDuration(Phase::LongBreak, seconds);
	}

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


	void PomodoroTimer::goToNextPhase()
	{
		using enum Phase;

        if (m_remainingTime != c_timeIsOut)
        {
            m_phase = m_phase == Work ? ShortBreak : Work;
        }
        else
        {
            if (m_phase == ShortBreak or m_phase == LongBreak)
            {
                m_phase = Work;
                reset();
            }
            else
            {
                m_currentSessionCount = m_phase == LongBreak ? 0 : ++m_currentSessionCount;
                emit pomodoroFinished(m_currentSessionCount);

                m_phase = m_currentSessionCount == m_sessionLength ? LongBreak : ShortBreak;

                start(m_phase);
            }

            emit timerFinished(m_phase);
        }

        emit phaseChanged(m_phase);
	}


	void PomodoroTimer::setPhaseDuration(const u16 seconds)
	{
        setPhaseDuration(m_phase, seconds);
	}


	void PomodoroTimer::setPhaseDuration(const Phase phase, const u16 seconds)
	{
		switch (phase)
		{
		    case Phase::Work:
		        m_workDuration = seconds;
		        emit phaseDurationChanged(seconds, Phase::Work);
		        return;

		    case Phase::ShortBreak:
		        m_shortBreakDuration = seconds;
		        emit phaseDurationChanged(seconds, Phase::ShortBreak);
		        return;

		    case Phase::LongBreak:
		        m_longBreakDuration = seconds;
		        emit phaseDurationChanged(seconds, Phase::LongBreak);
		}


	}


	void PomodoroTimer::setSessionLength(const u16 pomodoros)
	{
		if (m_sessionLength == pomodoros) [[unlikely]] return;

		m_sessionLength = pomodoros;
		emit sessionLengthChanged(pomodoros);
	}


    void PomodoroTimer::tick()
	{
        if (m_remainingTime == c_timeIsOut) [[unlikely]]
        {
            goToNextPhase();
            return;
        }

        emit remainingTimeChanged(--m_remainingTime);
	}

    void PomodoroTimer::updateRemainingTime(u16 seconds, Phase phase)
    {
    	if (m_phase != Phase::Work or m_state == State::Idle)
    	{
    		if (phase != m_phase) return;

    		m_remainingTime = seconds;
    		emit remainingTimeChanged(seconds);
    		return;
    	}



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

	PomodoroTimer::singleShotTimerUpdate::singleShotTimerUpdate(PomodoroTimer *parent, u16 seconds)
	: QObject{parent}
	, m_parent{parent}
	, m_isDone{false}
    {

    }
}
