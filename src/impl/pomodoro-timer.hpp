#pragma once

#include "../core/basic-types-aliases.hpp"
#include "../core/constants.hpp"

#include <QObject>
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
		Q_PROPERTY(u16 workDuration READ workDuration WRITE setWorkDuration NOTIFY workDurationChanged)
		Q_PROPERTY(u16 shortBreakDuration READ shortBreakDuration WRITE setShortBreakDuration NOTIFY shortBreakDurationChanged)
		Q_PROPERTY(u16 longBreakDuration READ longBreakDuration WRITE setLongBreakDuration NOTIFY longBreakDurationChanged)
		Q_PROPERTY(u16 sessionLength READ sessionLength NOTIFY sessionLengthChanged)
        Q_PROPERTY(u32 remainingTime READ remainingTime NOTIFY remainingTimeChanged)
        Q_PROPERTY(QString timeRemainingString READ timeRemainingString NOTIFY remainingTimeChanged)
        Q_PROPERTY(u32 currentSessionCount READ currentSessionCount NOTIFY pomodoroFinished)
        Q_PROPERTY(u16 currentPhaseDuration READ currentPhaseDuration NOTIFY phaseDurationChanged)

		static constexpr u16 c_timeIsOut{0};

	public:

		enum class Phase : u8 { Work, ShortBreak, LongBreak };
		Q_ENUM(Phase)

		enum class State : u8 { Idle, Running, Paused, AfkTimerRunning };
		Q_ENUM(State)

		struct CreateInfo
		{
			QObject *parent{nullptr};

		    u16 workPhaseDuration{  25 * 60 };
		    u16 shortBreakDuration{5 * 60};
		    u16 longBreakDuration{ 40 * 60};

		    u16 sessionLength{ defaults::SESSION_LENGTH };
		};

		explicit PomodoroTimer(QObject *parent = nullptr);
		explicit PomodoroTimer(const CreateInfo &data);

		[[nodiscard]] State state() const;
		[[nodiscard]] Phase phase() const;
		[[nodiscard]] u16 currentPhaseDuration() const;
		[[nodiscard]] u16 workDuration() const;
		[[nodiscard]] u16 shortBreakDuration() const;
		[[nodiscard]] u16 longBreakDuration() const;
		[[nodiscard]] u16 sessionLength() const;
		[[nodiscard]] u16 remainingTime() const;
        [[nodiscard]] QString timeRemainingString() const;
		[[nodiscard]] u16 currentSessionCount() const;

	public slots:

		void start();
		void start(Phase phase);
		void start(Phase phase, u16 seconds);
		void pause();
		void reset();
		void changeToNextPhase();

		void setPhaseDuration(u16 seconds);
		void setPhaseDuration(Phase phase, u16 seconds);
		void setWorkDuration(u16 seconds);
		void setShortBreakDuration(u16 seconds);
		void setLongBreakDuration(u16 seconds);
	    void setSessionLength(u16 pomodoros);

	private slots:

		void onTickUpdateRemainingTime();
		void onPhaseDurationChangeUpdateRemainingTime(u16 seconds, Phase phase);

		void setPhase(Phase phase);
		void setRemainingTime(u16 remainingTime);
		void setState(State state);

	signals:

		void stateChanged(State);
		void phaseChanged(Phase);
		void phaseDurationChanged(u16 seconds, Phase);
		void workDurationChanged(u16 seconds);
		void shortBreakDurationChanged(u16 seconds);
		void longBreakDurationChanged(u16 seconds);
		void sessionLengthChanged(u16 pomodoros);
		void remainingTimeChanged(u16 seconds);
		void pomodoroFinished(u16 currentSessionCount);
	    void timerFinished(Phase nextPhase);

	private:

	    u16 m_workDuration;
	    u16 m_shortBreakDuration;
	    u16 m_longBreakDuration;
	    u16 m_sessionLength;

		State m_state;
		Phase m_phase;
		u16 m_remainingTime;
		u16 m_currentSessionCount;

		QTimer m_timer;
	};
}