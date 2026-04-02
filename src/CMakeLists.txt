add_subdirectory(core)
add_subdirectory(impl)
add_subdirectory(ui)


qt_add_executable(Paz
	main.cpp
)

qt_add_qml_module(Paz
        URI PazQml
        VERSION 1.0
        QML_FILES
        ui/qml/Main.qml
)

target_link_libraries( Paz PRIVATE
		PazImplementation
		PazUI
		Qt6::Core
		Qt6::Widgets
        Qt6::Quick
        Qt6::Qml
)

target_compile_features(Paz PUBLIC cxx_std_23)