#pragma once

#include "core/basic-types-aliases.hpp"
#include "core/constants.hpp"

#include <QObject>
#include <QTime>
#include <QTimer>
#include <QtQml/qqmlregistration.h>


namespace impl
{
	class PomodoroTimer : public QObject
	{
		Q_OBJECT

		QML_NAMED_ELEMENT(PomodoroTimer)
        Q_PROPERTY(State state READ state NOTIFY stateChanged)
        Q_PROPERTY(Phase phase READ phase NOTIFY phaseChanged)
		Q_PROPERTY(QTime workDuration READ workDuration WRITE setWorkDuration NOTIFY workDurationChanged)
		Q_PROPERTY(QTime shortBreakDuration READ shortBreakDuration WRITE setShortBreakDuration NOTIFY shortBreakDurationChanged)
		Q_PROPERTY(QTime longBreakDuration READ longBreakDuration WRITE setLongBreakDuration NOTIFY longBreakDurationChanged)
		Q_PROPERTY(u16 sessionLength READ sessionLength NOTIFY sessionLengthChanged)
        Q_PROPERTY(QTime remainingTime READ remainingTime NOTIFY remainingTimeChanged)
        Q_PROPERTY(u32 currentSessionCount READ currentSessionCount NOTIFY pomodoroFinished)
        Q_PROPERTY(QTime currentPhaseDuration READ currentPhaseDuration NOTIFY phaseDurationChanged)
	    Q_PROPERTY(bool isAutoStartEnabled READ isPomodoroAutoStartEnabled NOTIFY pomodoroAutoStartChanged)

	public:

		enum class Phase : u8 { Work, ShortBreak, LongBreak };
		Q_ENUM(Phase)

		enum class State : u8 { Idle, Running, Paused, AfkTimerRunning };
		Q_ENUM(State)

		struct CreateInfo
		{
		    QTime workPhaseDuration{ defaults::WORK_DURATION};
		    QTime shortBreakDuration{defaults::SHORT_BREAK_DURATION};
		    QTime longBreakDuration{defaults::LONG_BREAK_DURATION};

		    u16 sessionLength{defaults::SESSION_LENGTH};
		    bool isAutoStartEnabled{defaults::AUTOSTART_NEW_POMODORO};
		};

		explicit PomodoroTimer(QObject *parent = nullptr) noexcept;
		explicit PomodoroTimer(QObject *parent, const CreateInfo &data) noexcept;

		[[nodiscard]] auto state() const noexcept -> State;
		[[nodiscard]] auto phase() const noexcept -> Phase;
		[[nodiscard]] auto currentPhaseDuration() const -> QTime;
		[[nodiscard]] auto workDuration() const noexcept -> QTime;
		[[nodiscard]] auto shortBreakDuration() const noexcept -> QTime;
		[[nodiscard]] auto longBreakDuration() const noexcept -> QTime;
		[[nodiscard]] auto sessionLength() const noexcept -> u16;
		[[nodiscard]] auto remainingTime() const noexcept -> QTime;
		[[nodiscard]] auto currentSessionCount() const noexcept -> u16;
        [[nodiscard]] auto isPomodoroAutoStartEnabled() const noexcept -> bool;

	public slots:

		void start() noexcept;
		void start(Phase phase) noexcept;
		void start(Phase phase, QTime duration) noexcept;
		void pause() noexcept;
		void reset() noexcept;
		void changeToNextPhase() noexcept;

	    void togglePomodoroAutoStart() noexcept;

		void setPhaseDuration(QTime duration) noexcept;
		void setPhaseDuration(Phase phase, QTime duration) noexcept;
		void setWorkDuration(QTime duration) noexcept;
		void setShortBreakDuration(QTime duration) noexcept;
		void setLongBreakDuration(QTime duration) noexcept;
	    void setSessionLength(u16 pomodoros) noexcept;

	private slots:

		void onTickUpdateRemainingTime() noexcept;
		void onPhaseDurationChangeUpdateRemainingTime(Phase phase, QTime duration) noexcept;
		void enablePomodoroAutoStart() noexcept;

		void setPhase(Phase phase) noexcept;
		void setRemainingTime(QTime remainingTime) noexcept;
		void setState(State state) noexcept;

	signals:

		void stateChanged(State);
		void phaseChanged(Phase);
		void phaseDurationChanged(Phase, QTime);
		void workDurationChanged(QTime);
		void shortBreakDurationChanged(QTime);
		void longBreakDurationChanged(QTime);
		void sessionLengthChanged(u16 pomodoros);
		void remainingTimeChanged(QTime);
		void pomodoroFinished(u16 currentSessionCount);
	    void timerFinished(Phase nextPhase);
	    void pomodoroAutoStartChanged(bool isEnabled);

	private:

	    QTime m_workDuration;
	    QTime m_shortBreakDuration;
	    QTime m_longBreakDuration;
	    u16 m_sessionLength;

		State m_state;
		Phase m_phase;
		QTime m_remainingTime;
		u16 m_currentSessionCount;

	    bool m_isWorkPhaseAutoStartEnabled;

		QTimer m_timer;
	};
}