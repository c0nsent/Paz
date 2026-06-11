add_subdirectory(core)
add_subdirectory(impl)

qt_add_executable(Paz
	main.cpp
)

add_subdirectory(ui)

target_link_libraries(Paz PRIVATE
		PazImplementation
		Qt6::Core
		Qt6::Widgets
        Qt6::Quick
        Qt6::Qml
)

target_compile_features(Paz PUBLIC cxx_std_23)