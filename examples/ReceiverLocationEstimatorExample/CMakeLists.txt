project(ReceiverLocationEstimatorExample)

add_executable(${PROJECT_NAME}
	main.cpp
)

target_link_libraries(${PROJECT_NAME} ReceiverLocationEstimator)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Examples")