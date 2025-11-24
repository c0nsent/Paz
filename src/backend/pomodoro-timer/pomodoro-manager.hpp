/**
 * @date 11/24/25
 * 
 * @author amitayus_
 */

#pragma once

#include "timer-engine.hpp"
#include "pomodoro-phase.hpp"

namespace paz::backend::pt
{
	class PomodoroManager : public QObject
	{
		Q_OBJECT

	public:

		explicit PomodoroManager(QObject *parent = nullptr);

	public slots:

	private slots:

	signals:

	private:

		TimerEngine m_timerEngine;
		PomodoroPhase m_phase;


	};
}