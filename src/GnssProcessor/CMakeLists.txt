project(GnssProcessor)

set(WRAPPERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Wrappers)
set(STORAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Storage)
set(TRACKER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SatTracker)

set ( General
	IGnssProcessor.h
	IGnssProcessorStrategy.h
	IDataInput.h

	GnssProcessorStrategy.h
	GnssProcessorStrategy.cpp

	GnssProcessor.h
	GnssProcessor.cpp

	GnssProcessorStrategyFactory.h
	GnssProcessorStrategyFactory.cpp
)
source_group (General FILES ${General})

set ( Storage
	${STORAGE_DIR}/IGnssStorage.h

	${STORAGE_DIR}/GnssStorage.cpp
	${STORAGE_DIR}/GnssStorage.h

	${STORAGE_DIR}/ISatStorage.h
	${STORAGE_DIR}/IGPSSatStorage.h
	${STORAGE_DIR}/GPSSatStorage.h
	${STORAGE_DIR}/GPSSatStorage.cpp
)
source_group (Storage FILES ${Storage})

set ( Wrappers
	${WRAPPERS_DIR}/GPSFrameParserStorageWrapper.h
	${WRAPPERS_DIR}/GPSFrameParserStorageWrapper.cpp

	${WRAPPERS_DIR}/GPSSatLocEstStorageWrapper.h
	${WRAPPERS_DIR}/GPSSatLocEstStorageWrapper.cpp

	${WRAPPERS_DIR}/RecvEstStorageWrapper.h
	${WRAPPERS_DIR}/RecvEstStorageWrapper.cpp
)
source_group (Wrappers FILES ${Wrappers})

set( SatTracker
	${TRACKER_DIR}/SatTracker.h
	${TRACKER_DIR}/SatTrackerFactory.h
	${TRACKER_DIR}/SatTrackerFactory.cpp
)
source_group (SatTracker FILES ${SatTracker})

add_library(${PROJECT_NAME} STATIC
	${General}
	${SatTracker}
	${Storage}
	${Wrappers}
)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${WRAPPERS_DIR}
	PUBLIC ${STORAGE_DIR}
	PUBLIC ${TRACKER_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC FrameParser
	PUBLIC ReceiverLocationEstimator
	PUBLIC SatLocationEstimator
)