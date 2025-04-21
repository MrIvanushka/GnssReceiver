project(SatLocationEstimator)

set(GLONASS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Glonass)
set(GPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/GPS)

set ( General
	ISatLocationEstimator.h
	IEphemerisStorage.h

	SatLocationEstimatorFactory.cpp
	SatLocationEstimatorFactory.h
)
source_group (General FILES ${General})

set ( GPS
	${GPS_DIR}/IGPSEphemerisStorage.h
	${GPS_DIR}/GPSSatLocationEstimator.cpp
	${GPS_DIR}/GPSSatLocationEstimator.h
)
source_group (GPS FILES ${GPS})

set ( Glonass
	${GLONASS_DIR}/IGlonassEphemerisStorage.h
	${GLONASS_DIR}/GlonassSatLocationEstimator.cpp
	${GLONASS_DIR}/GlonassSatLocationEstimator.h
)
source_group (Glonass FILES ${Glonass})

add_library(${PROJECT_NAME} STATIC
	${General}
	${GPS}
	${Glonass}
)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${GPS_DIR}
	PUBLIC ${GLONASS_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC CommonUtilities
	PUBLIC Math
)