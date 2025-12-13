/**
 * @date 11/19/25
 * 
 * @author amitayus_
 */

#pragma once

#include <chrono>
#include <limits>
#include <qstring.h>
#include <QtTypes>
#include <QVarLengthArray>
#include <QHash>


///Неймспейс с константами, задающими ограничения для значений
namespace limits
{
	/// Максимальная длительность фазы - 99 минут
	constexpr quint16 c_maxPhaseDuration{99 * 60};
	/// Минимальная длительность фазы - 1 минута
	constexpr quint16 c_minPhaseDuration{1 * 60};

	/// Максимальное количество помодоро за сессию
	constexpr quint16 c_maxPomodoro{std::numeric_limits<quint16>::max() - 1};

	constexpr quint16 c_maxSessionLength{99};
	constexpr quint16 c_minSessionLength{1};
}

/// Неймспейс с константами, задающими значение по-умолчанию
namespace defaults
{
	using namespace std::chrono_literals;

	///Количество фаз в помодоро таймере
	constexpr std::size_t c_phaseCount{3};

	constexpr std::size_t c_timerStateCount{3};

	/// Интервал тика QTimer в миллисекундах
	constexpr auto c_timerInterval{1000ms};

	static const QVarLengthArray<quint16> c_phaseDurations
	{
		/// Длительности фазы `PhaseManager::Phase::Work` по-умолчанию
		25 * 60,
		/// Длительности фазы `PhaseManager::Phase::ShortBreak` по-умолчанию
		5 * 60,
		/// Длительности фазы `PhaseManager::Phase::LongBreak` по-умолчанию
		45 * 60
	};


	static constexpr quint16 c_invalidPhaseDuration{0};

	constexpr quint16 c_sessionLength{6};

	constexpr auto c_fontFamily{"Adwaita Sans"};
	constexpr quint8 c_fontSize{14};
	constexpr bool c_isBold{false};
}

namespace settings
{
	namespace groups
	{
		constexpr auto c_pomodoroTimer{"PomodoroTimer"};
		constexpr auto c_style{"Style"};
	}
	namespace keys
	{
		constexpr auto c_workDuration{"WorkDuration"};
		constexpr auto c_shortBreakDuration{"ShortBreakDuration"};
		constexpr auto  c_longBreakDuration{"LongBreakDuration"};

		constexpr auto c_sessionLength{"SessionLength"};

		constexpr auto c_fontFamily{"FontFamily"};
		constexpr auto c_fontSize{"FontSize"};
		constexpr auto c_isBold{"IsBold"};
	}
}