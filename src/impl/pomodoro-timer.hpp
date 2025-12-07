/**
 * @date 12/4/25
 * 
 * @author amitayus_
 */

#pragma once


#include "../core/constants.hpp"

#include <QObject>
#include <QTimer>

#include <chrono>

namespace paz::impl
{
	class PomodoroTimer final : public QObject
	{
		Q_OBJECT

		static constexpr quint16 c_timeIsOut{0};

	public:

		enum class Phase : quint8 { Work, ShortBreak, LongBreak };
		Q_ENUM(Phase)

		explicit PomodoroTimer(QObject *parent = nullptr);

		[[nodiscard]] bool isActive() const;

		[[nodiscard]] quint16 currentPhaseDuration() const;

		[[nodiscard]] quint16 remainingTime() const;

	public slots:

		void start();
		void start(quint16 duration);
		void pause();
		void reset();
		void toNextPhase();

		void setPhaseDuration(Phase phase, quint16 duration);
		void setAllPhaseDurations(
			quint16 work,
			quint16 shortBreak,
			quint16 longBreak
		);
		void setSessionLength(quint16 pomodoros);

	private slots:

		void handleQTimerTimeout();
		
	signals:

		void started();
		void paused();
		void finished();

		void remainingTimeChanged(quint16);
		
		void phaseChanged(Phase);
		void phaseDurationChanged(Phase, quint16);
		void sessionLengthChanged(quint16);
		void pomodoroFinished(quint16 currentSessionCount);
		//void breakFinished(Phase);
	
	private:

		Phase m_currentPhase;
		quint16 m_phaseDurations[defaults::c_phaseCount];
		quint16 m_sessionLength;

		quint16 m_remainingTime;
		quint16 m_currentSessionCount;

		QTimer m_timer;
	};
}
