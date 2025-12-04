add_subdirectory(core)
add_subdirectory(impl)
add_subdirectory(ui)
#add_subdirectory(logging)

qt_add_executable(Paz
	main.cpp
)

target_link_libraries( Paz PRIVATE
		PazImplementation
		PazUI
		#PazLogging
		Qt6::Core
		Qt6::Widgets
)

target_compile_features(Paz PUBLIC cxx_std_23)