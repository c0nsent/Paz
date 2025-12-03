qt_add_library(PazUI STATIC
		main-window.cpp main-window.hpp
		pomodoro-timer/pomodoro-timer-widget.cpp pomodoro-timer/pomodoro-timer-widget.hpp
)

target_link_libraries(PazUI PRIVATE
		PazImplementation
		PazCore
		Qt6::Core
		Qt6::Widgets
)

target_compile_features(PazUI PUBLIC cxx_std_23)

# target_include_directories(PazUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
