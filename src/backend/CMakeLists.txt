qt_add_library(PazBackend SHARED
		pomodoro-timer/pomodoro-manager.cpp pomodoro-timer/pomodoro-manager.hpp
		pomodoro-timer/pomodoro-phase.cpp pomodoro-timer/pomodoro-phase.hpp
		pomodoro-timer/timer-engine.cpp pomodoro-timer/timer-engine.hpp
)

target_link_libraries(PazBackend PRIVATE
		PazCore
		Qt6::Core
)

target_include_directories(PazBackend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})