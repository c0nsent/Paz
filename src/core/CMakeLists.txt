qt_add_library(PazCore STATIC
		enums.hpp
		constants.hpp
		#main.cpp
)

target_link_libraries(PazCore PRIVATE
		Qt6::Core
)

target_compile_features(PazCore PUBLIC cxx_std_23)

