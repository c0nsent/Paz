#pragma once

#include "basic-types-aliases.hpp"

#include <chrono>
#include <limits>
#include <QTime>


namespace limits
{
    /// Максимальная длительность фазы - 99 минут
    constexpr u16 MAX_PHASE_DURATION{99 * 60};
    /// Минимальная длительность фазы - 1 минута
    constexpr u16 MIN_PHASE_DURATION{1 * 60};

    constexpr u16 MAX_POMODORO{std::numeric_limits<u16>::max() - 1};

    constexpr u16 MAX_SESSION_LENGTH{99};
    constexpr u16 MIN_SESSION_LENGTH{1};

    static constexpr u16 INVALID_PHASE_DURATION{0};
}

/// Неймспейс с константами, задающими значение по-умолчанию
namespace defaults
{
    using namespace std::chrono_literals;

    /// Интервал тика QTimer в миллисекундах
    constexpr auto TIMER_INTERVAL{1000ms};

    constexpr bool AUTOSTART_NEW_POMODORO{true};

    ///Это в секундах
    constexpr u16 WORK_DURATION{25 * 60};
    constexpr u16 SHORT_BREAK_DURATION{5 * 60};
    constexpr u16 LONG_BREAK_DURATION{45 * 60};

    constexpr u16 SESSION_LENGTH{6};

    constexpr auto FONT_FAMILY{"Adwaita Sans"};
    constexpr quint8 FONT_SIZE{14};
    constexpr bool IS_BOLD{false};
}


namespace settings
{
    namespace grps
    {
        constexpr auto POMODORO_TIMER{"PomodoroTimer"};
        constexpr auto STYLE{"Style"};
    }

    namespace keys
    {

        constexpr auto AUTOSTART_NEW_POMODORO{"AutostartNewPomodoro"};

        constexpr auto WORK_DURATION{"WorkDuration"};
        constexpr auto SHORT_BREAK_DURATION{"ShortBreakDuration"};
        constexpr auto LONG_BREAK_DURATION{"LongBreakDuration"};

        constexpr auto SESSION_LENGTH{"SessionLength"};

        constexpr auto FONT_FAMILY{"FontFamily"};
        constexpr auto FONT_SIZE{"FontSize"};
        constexpr auto IS_BOLD{"IsBold"};
    }
}