#pragma once

#include "basic-types-aliases.hpp"

#include <chrono>
#include <limits>
#include <QTime>


namespace limits
{
    /// Максимальная длительность фазы - 99 минут
    const QTime MAX_PHASE_DURATION{0, 99};
    /// Минимальная длительность фазы - 1 минута
    const QTime MIN_PHASE_DURATION{0, 1};

    constexpr u16 MAX_POMODORO{std::numeric_limits<decltype(MAX_POMODORO)>::max() - 1};

    constexpr u16 MAX_SESSION_LENGTH{99};
    constexpr u16 MIN_SESSION_LENGTH{1};
}

/// Неймспейс с константами, задающими значение по-умолчанию
namespace defaults
{
    using namespace std::chrono_literals;

    constexpr auto TIMER_INTERVAL{1000ms};

    constexpr bool AUTOSTART_NEW_POMODORO{true};

    const QTime WORK_DURATION{0, 25};
    const QTime SHORT_BREAK_DURATION{0, 5};
    const QTime LONG_BREAK_DURATION{0, 45};

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