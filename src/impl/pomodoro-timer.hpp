#pragma once

#include "../core/basic-types-aliases.hpp"
#include "../core/constants.hpp"

#include <QHash>
#include <QMetaEnum>
#include <QObject>
#include <QTimer>

#include <initializer_list>


namespace impl
{
	class PomodoroTimer : public QObject
	{
		Q_OBJECT

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

			State state{ State::Idle };
			Phase phase{ Phase::Work };

			QHash<Phase,u16> phaseDurations{ initializePhaseDurations() };

			u16 sessionLength{ defaults::SESSION_LENGTH };
			u16 currentSessionCount{};
		};

		explicit PomodoroTimer(QObject *parent = nullptr);
		explicit PomodoroTimer(const CreateInfo &data);

		[[nodiscard]] State state() const;
		[[nodiscard]] Phase phase() const;
	    //[[nodiscard]] auto phaseLabel() const -> const char *;
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

		void setPhaseDuration(u16 current);
		void setPhaseDuration(Phase phase, u16 seconds);
		void setPhaseDuration(const std::initializer_list<std::pair<Phase, u16>> &phaseDurations);

		void setSessionLength(u16 pomodoros);

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

	private:

		static QHash<Phase, u16> initializePhaseDurations();

		State m_state;
		Phase m_phase;
		QHash<Phase, u16> m_phaseDurations;
		u16 m_sessionLength;

		u16 m_remainingTime;
		u16 m_currentSessionCount;

		QTimer m_timer;
	};
}