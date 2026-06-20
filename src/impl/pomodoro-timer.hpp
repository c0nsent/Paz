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
        Q_PROPERTY(u32 remainingTime READ remainingTime NOTIFY remainingTimeChanged)
        Q_PROPERTY(QString timeRemainingString READ timeRemainingString NOTIFY remainingTimeChanged)
        Q_PROPERTY(u32 currentSessionCount READ currentSessionCount NOTIFY pomodoroFinished)
        Q_PROPERTY(u16 currentPhaseDuration READ phaseDuration NOTIFY phaseDurationChanged)

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
		[[nodiscard]] u16 phaseDuration() const;
		[[nodiscard]] u16 phaseDuration(Phase phase) const;
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
		void toNextPhase();

		void setPhaseDuration(u16 seconds);
		void setPhaseDuration(Phase phase, u16 seconds);
	    void setSessionLength(u16 pomodoros);

	    void readSettings();
	    void writeSettings();

	private slots:

		void updateRemainingTime();

		bool trySetPhase(Phase phase);
		bool trySetRemainingTime(u16 remainingTime);
		bool trySetState(State state);

	signals:

		void stateChanged(State);
		void phaseChanged(Phase);
		void phaseDurationChanged(u16 seconds, Phase);
		void sessionLengthChanged(u16 pomodoros);
		void remainingTimeChanged(u16 seconds);
		void pomodoroFinished(u16 currentSessionCount);
	    void timeIsOut();

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