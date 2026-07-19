#include "pomodoro-timer.hpp"

#include <QMetaEnum>


namespace impl
{
    PomodoroTimer::PomodoroTimer(QObject *parent) noexcept : PomodoroTimer(parent, CreateInfo{}) {}


    PomodoroTimer::PomodoroTimer(QObject *parent, const CreateInfo &data) noexcept
        : QObject{parent}
        , m_workDuration{data.workPhaseDuration}
        , m_shortBreakDuration{data.shortBreakDuration}
        , m_longBreakDuration{data.workPhaseDuration}
        , m_sessionLength{data.sessionLength}
        , m_state{State::Idle}
        , m_phase{Phase::Work}
        , m_remainingTime{m_workDuration}
        , m_currentSessionCount{0}
        , m_isWorkPhaseAutoStartEnabled(data.isAutoStartEnabled)
    {
        m_timer.setTimerType(Qt::CoarseTimer);
        m_timer.setInterval(defaults::TIMER_INTERVAL);

        connect(&m_timer, &QTimer::timeout, this, &PomodoroTimer::onTickUpdateRemainingTime);
        connect(this,
            &PomodoroTimer::phaseDurationChanged,
            this,
            &PomodoroTimer::onPhaseDurationChangeUpdateRemainingTime
        );

        if (m_isWorkPhaseAutoStartEnabled) enablePomodoroAutoStart();
    }


	auto PomodoroTimer::state() const noexcept -> State {return m_state;}

	auto PomodoroTimer::phase() const noexcept -> Phase {return m_phase;}


    auto PomodoroTimer::currentPhaseDuration() const -> QTime
    {
        switch (m_phase)
        {
            case Phase::Work: return m_workDuration;
            case Phase::ShortBreak: return m_shortBreakDuration;
            case Phase::LongBreak: return m_longBreakDuration;
        }

        return QTime{};
    }


	auto PomodoroTimer::workDuration() const noexcept -> QTime { return m_workDuration; }

    auto PomodoroTimer::shortBreakDuration() const noexcept-> QTime { return m_shortBreakDuration; }

	auto PomodoroTimer::longBreakDuration() const noexcept -> QTime { return m_longBreakDuration; }
	auto PomodoroTimer::sessionLength() const noexcept -> u16 {return m_sessionLength;}

	auto PomodoroTimer::remainingTime() const noexcept -> QTime {return m_remainingTime;}

	auto PomodoroTimer::currentSessionCount() const noexcept -> u16 {return m_currentSessionCount;}

    auto PomodoroTimer::isPomodoroAutoStartEnabled() const noexcept -> bool { return m_isWorkPhaseAutoStartEnabled; }


    void PomodoroTimer::start() noexcept
    {
        if (m_state == State::Running) return;

        setState(State::Running);
        m_timer.start();
    }


    void PomodoroTimer::start(const Phase phase) noexcept { start(phase, currentPhaseDuration()); }

	void PomodoroTimer::start(const Phase phase, const QTime duration) noexcept
    {
        setPhase(phase);
        setRemainingTime(duration);

        start();
    }


	void PomodoroTimer::pause() noexcept
    {
        if (m_state != State::Running) [[unlikely]] return;

        setState(State::Paused);
        m_timer.stop();
    }


	void PomodoroTimer::reset() noexcept
    {
        setState(State::Idle);
        setRemainingTime(currentPhaseDuration());

        m_timer.stop();
    }


	void PomodoroTimer::changeToNextPhase() noexcept
    {
        using enum Phase;

        if (m_remainingTime == QTime{0, 0})
        {
            m_phase = m_phase == Work ? ShortBreak : Work;
            start(m_phase);
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

    void PomodoroTimer::togglePomodoroAutoStart() noexcept
    {
        m_isWorkPhaseAutoStartEnabled = not m_isWorkPhaseAutoStartEnabled;

        if (m_isWorkPhaseAutoStartEnabled)
        {
            connect(this, &PomodoroTimer::timerFinished,
                this,&PomodoroTimer::enablePomodoroAutoStart);

            return;
        }

        disconnect(this, &PomodoroTimer::timerFinished,
            this, &PomodoroTimer::enablePomodoroAutoStart);
    }


    void PomodoroTimer::setPhaseDuration(const QTime duration) noexcept
    {
        setPhaseDuration(m_phase, duration);
    }


	void PomodoroTimer::setPhaseDuration(const Phase phase, const QTime duration) noexcept
    {
        switch (phase)
        {
            case Phase::Work:
                m_workDuration = duration;
                emit phaseDurationChanged(Phase::Work, duration);
                return;

            case Phase::ShortBreak:
                m_shortBreakDuration = duration;
                emit phaseDurationChanged(Phase::ShortBreak, duration);
                return;

            case Phase::LongBreak:
                m_longBreakDuration = duration;
                emit phaseDurationChanged(Phase::LongBreak, duration);
        }
    }


	void PomodoroTimer::setWorkDuration(const QTime duration) noexcept
    {
        setPhaseDuration(Phase::Work, duration);
    }

	void PomodoroTimer::setShortBreakDuration(const QTime duration) noexcept
    {
        setPhaseDuration(Phase::ShortBreak, duration);
    }


	void PomodoroTimer::setLongBreakDuration(const QTime duration) noexcept
    {
        setPhaseDuration(Phase::LongBreak, duration);
    }


	void PomodoroTimer::setSessionLength(const u16 pomodoros) noexcept
    {
        if (m_sessionLength == pomodoros) [[unlikely]] return;

        m_sessionLength = pomodoros;
        emit sessionLengthChanged(pomodoros);
    }


    void PomodoroTimer::onTickUpdateRemainingTime() noexcept
    {
        if (m_remainingTime.msecsSinceStartOfDay() == 0) [[unlikely]]
        {
            changeToNextPhase();
            return;
        }

        m_remainingTime = m_remainingTime.addSecs(-1);
        emit remainingTimeChanged(m_remainingTime);
    }


    void PomodoroTimer::onPhaseDurationChangeUpdateRemainingTime(const Phase phase, const QTime duration) noexcept
    {
        if (m_phase != Phase::Work or m_state == State::Idle)
        {
            if (phase != m_phase) return;

            m_remainingTime = duration;
            emit remainingTimeChanged(duration);
        }
    }

    void PomodoroTimer::enablePomodoroAutoStart() noexcept
    {
        if (m_phase == Phase::Work) start();
    }


    void PomodoroTimer::setPhase(const Phase phase) noexcept
    {
        if (m_phase == phase) [[unlikely]] return;

        m_phase = phase;
        emit phaseChanged(m_phase);
    }


	void PomodoroTimer::setRemainingTime(const QTime remainingTime) noexcept
    {
        if (m_remainingTime == remainingTime) [[unlikely]] return;

        m_remainingTime = remainingTime;
        emit remainingTimeChanged(m_remainingTime);
    }


    void PomodoroTimer::setState(const State state) noexcept
    {
        if (m_state == state) [[unlikely]] return;

        m_state = state;
        emit stateChanged(m_state);
    }
}