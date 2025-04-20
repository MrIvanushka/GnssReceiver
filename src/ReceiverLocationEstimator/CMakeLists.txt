project(ReceiverLocationEstimator)

set ( General
	IReceiverLocationEstimator.h
	ISatelliteTable.h

	CommonReceiverLocationEstimator.cpp
	CommonReceiverLocationEstimator.h

	ReceiverLocationEstimatorFactory.cpp
	ReceiverLocationEstimatorFactory.h
)
source_group (General FILES ${General})

add_library(${PROJECT_NAME} STATIC
	${General}
)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC CommonUtilities
	PUBLIC Math
)