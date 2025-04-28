project(AbsoluteShiftEstimationExample)

add_executable(${PROJECT_NAME}
	main.cpp
)

target_link_libraries(${PROJECT_NAME} FrameParser)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Examples")