/**
 * @date 12/4/25
 * 
 * @author amitayus_
 */

#pragma once


#include <QMetaEnum>

#include "../core/constants.hpp"

#include <QHash>
#include <QObject>
#include <QTimer>

#include <initializer_list>


namespace impl
{
	class PomodoroTimer final : public QObject
	{
		Q_OBJECT

		static constexpr quint16 c_timeIsOut{0};

	public:

		enum class Phase : quint8 { Work, ShortBreak, LongBreak };
		Q_ENUM(Phase)

		enum class State : quint8 { Idle, Running, Paused, AfkTimerRunning };
		Q_ENUM(State)

		struct Initializer
		{
			QObject *parent{nullptr};

			State state{ State::Idle };
			Phase phase{ Phase::Work };

			QHash<Phase,quint16> phaseDurations{ initializePhaseDurations() };

			quint16 sessionLength{ defaults::c_sessionLength };
			quint16 currentSessionCount{};
		};

		PomodoroTimer(Initializer &&data);

		[[nodiscard]] State state() const;
		[[nodiscard]] Phase phase() const;
		[[nodiscard]] quint16 phaseDuration() const;
		[[nodiscard]] quint16 phaseDuration(Phase phase) const;
		[[nodiscard]] quint16 sessionLength() const;
		[[nodiscard]] quint16 remainingTime() const;
		[[nodiscard]] quint16 currentSessionCount() const;

	public slots:

		void start();
		void start(Phase phase);
		void start(Phase phase, quint16 seconds);
		void pause();
		void reset();
		void toNextPhase();

		void setPhaseDuration(quint16 current);
		void setPhaseDuration(Phase phase, quint16 seconds);
		void setPhaseDuration(const std::initializer_list<std::pair<Phase, quint16>> &phaseDurations);

		void setSessionLength(quint16 pomodoros);

	private slots:

		void updateRemainingTime();

		bool trySetPhase(Phase phase);
		bool trySetRemainingTime(quint16 remainingTime);
		bool trySetState(State state);
		
	signals:

		void stateChanged(State);
		void phaseChanged(Phase);
		void phaseDurationChanged(quint16 seconds, Phase);
		void sessionLengthChanged(quint16 pomodoros);
		void remainingTimeChanged(quint16 seconds);
		void pomodoroFinished(quint16 currentSessionCount);
	
	private:

		static QHash<Phase, quint16> initializePhaseDurations();

		State m_state;
		Phase m_phase;
		QHash<Phase, quint16> m_phaseDurations;
		quint16 m_sessionLength;

		quint16 m_remainingTime;
		quint16 m_currentSessionCount;

		QTimer m_timer;
	};
}
