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

	public:

		enum class Phase : quint8 { Work, ShortBreak, LongBreak };
		Q_ENUM(Phase)

		explicit PomodoroTimer(QObject *parent = nullptr);

		explicit PomodoroTimer(
			Phase currentPhase,
			std::chrono::seconds workPhase,
			std::chrono::seconds shortBreakPhase,
			std::chrono::seconds longBreakPhase,
			qint64 sessionLength,
			QObject *parent = nullptr
		);

		bool isActive() const;

	public slots:

		void start();
		void start(std::chrono::seconds duration);
		void pause();
		void reset();
		void toNextPhase();

		void setPhaseDuration(Phase phase, std::chrono::seconds duration);
		void setSessionLength(qint64 pomodoros);

	private slots:

		void handleQTimerTimeout();
		
	signals:

		void started();
		void paused();
		void finished();

		void remainingTimeChanged(std::chrono::seconds remainingTime);
		
		void phaseChanged(Phase);
		void phaseDurationChanged(Phase, std::chrono::seconds);
		void sessionLengthChanged(qint64);
		void pomodoroFinished(qint64 currentSessionCount);
	
	private:

		Phase m_currentPhase;
		std::chrono::seconds m_phaseDurations[defaults::c_phaseCount];
		qint64 m_sessionLength;

		std::chrono::seconds m_remainingTime;
		qint64 m_currentSessionCount;

		QTimer m_timer;
	};
}
