#pragma once

#include "basic-types-aliases.hpp"

#include <chrono>
#include <limits>
#include <QVarLengthArray>


namespace limits
{
	/// Максимальная длительность фазы - 99 минут
	constexpr u16 MAX_PHASE_DURATION{99 * 60};
	/// Минимальная длительность фазы - 1 минута
	constexpr u16 MIN_PHASE_DURATION{1 * 60};

	/// Максимальное количество помодоро за сессию
	constexpr u16 MAX_POMODORO{std::numeric_limits<u16>::max() - 1};

	constexpr u16 MAX_SESSION_LENGTH{99};
	constexpr u16 MIN_SESSION_LENGTH{1};
}

/// Неймспейс с константами, задающими значение по-умолчанию
namespace defaults
{
	using namespace std::chrono_literals;

	///Количество фаз в помодоро таймере
	constexpr std::size_t PHASE_COUNT{3};

	constexpr std::size_t TIMER_STATE_COUNT{3};

    /// Интервал тика QTimer в миллисекундах
	constexpr auto TIMER_INTERVAL{1000ms};
    static constexpr u16 PHASE_DURATIONS[]
    {
        25 * 60,
        5 * 60,
        45 * 60
    };

    static constexpr u16 INVALID_PHASE_DURATION{0};

	constexpr u16 SESSION_LENGTH{6};

	constexpr auto FONT_FAMILY{"Adwaita Sans"};
	constexpr quint8 FONT_SIZE{14};
	constexpr bool IS_BOLD{false};
}


namespace settings
{
	namespace groups
	{
		constexpr auto POMODORO_TIMER{"PomodoroTimer"};
		constexpr auto STYLE{"Style"};
	}
	namespace keys
	{
		static const QVarLengthArray PHASE_DURATIONS
		{
			"WorkDuration", "ShortBreakDuration", "LongBreakDuration"
		};

		constexpr auto SESSION_LENGTH{"SessionLength"};

		constexpr auto FONT_FAMILY{"FontFamily"};
		constexpr auto FONT_SIZE{"FontSize"};
		constexpr auto IS_BOLD{"IsBold"};
	}
}