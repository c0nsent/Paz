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


///Неймспейс с константами, задающими ограничения для значений
namespace limits
{
	/// Максимальная длительность фазы - 99 минут
	static constexpr quint16 c_maxPhaseDuration{99 * 60};
	/// Минимальная длительность фазы - 1 минута
	static constexpr quint16 c_minPhaseDuration{1 * 60};

	/// Максимальное количество помодоро за сессию
	static constexpr quint16 c_maxPomodoro{std::numeric_limits<quint16>::max() - 1};

	static constexpr quint16 c_maxSessionLength{99};
	static constexpr quint16 c_minSessionLength{1};
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

	/// Длительности фазы `PhaseManager::Phase::Work` по-умолчанию
	static constexpr quint16 c_workDuration{25 * 60};
	/// Длительности фазы `PhaseManager::Phase::ShortBreak` по-умолчанию
	static constexpr quint16 c_shortBreakDuration{5 * 60};
	/// Длительности фазы `PhaseManager::Phase::LongBreak` по-умолчанию
	static constexpr quint16 c_longBreakDuration{45 * 60};

	static constexpr qint64 c_sessionLength{6};

	static constexpr auto c_fontFamily{"Adwaita Sans"};
	static constexpr quint8 c_fontSize{14};
	static constexpr bool c_isBold{false};
}

namespace settings
{
	namespace groups
	{
		static constexpr auto c_pomodoroTimer{"PomodoroTimer"};
		static constexpr auto c_style{"Style"};
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