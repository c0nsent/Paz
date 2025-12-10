add_subdirectory(core)
add_subdirectory(impl)
add_subdirectory(ui)


qt_add_executable(Paz
	main.cpp
)

add_dependencies(Paz CopyStyleFile)

target_link_libraries( Paz PRIVATE
		PazImplementation
		PazUI
		Qt6::Core
		Qt6::Widgets
)

target_compile_features(Paz PUBLIC cxx_std_23)