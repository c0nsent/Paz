qt_add_library(PazUI SHARED
		pomodoro-timer-widget.cpp pomodoro-timer-widget.hpp
)

target_link_libraries(PazUI PRIVATE
		PazImplementation
		PazCore
		Qt6::Core
		Qt6::Widgets
)

target_compile_features(PazUI PUBLIC cxx_std_23)
