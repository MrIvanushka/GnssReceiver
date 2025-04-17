cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(FrameParser)

set(COLLECTORS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Collectors)
set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Headers)
set(PROCESSORS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/MessageProcessors)

set ( General
	General/Context.h
	General/Context.cpp
	General/Stat.h
	General/Stat.cpp
	General/Log.h
	
	IFrameParser.h
	GPSFrameParser.cpp
	GPSFrameParser.h
)
source_group (General FILES ${General})

set ( SubframeCollector
	${COLLECTORS_DIR}/SubframeCollector.h
	${COLLECTORS_DIR}/SubframeCollector.cpp
	${COLLECTORS_DIR}/WordCollector.h
	${COLLECTORS_DIR}/WordCollector.cpp
	${COLLECTORS_DIR}/BitCollector.h
	${COLLECTORS_DIR}/BitCollector.cpp
	${COLLECTORS_DIR}/ByteCollector.h
	${COLLECTORS_DIR}/ByteCollector.cpp
	${COLLECTORS_DIR}/SyncrobyteSeeker.h
	${COLLECTORS_DIR}/SyncrobyteSeeker.cpp
)
source_group (SubframeCollector FILES ${SubframeCollector})

set ( Headers
	${HEADERS_DIR}/EphemerisHeader.h
	${HEADERS_DIR}/HandoverWordHeader.h
	${HEADERS_DIR}/SatClockHeader.h
)
source_group (Headers FILES ${Headers})

set ( Processors
	${PROCESSORS_DIR}/IDataProcessor.h
	${PROCESSORS_DIR}/EphemerisProcessor.h
	${PROCESSORS_DIR}/SubframeProcessor.h
	${PROCESSORS_DIR}/SatClockProcessor.h
	${PROCESSORS_DIR}/EphemerisProcessor.cpp
	${PROCESSORS_DIR}/SubframeProcessor.cpp
	${PROCESSORS_DIR}/SatClockProcessor.cpp
)
source_group (Processors FILES ${Processors})

set ( Utility
	ByteData.h
	ByteData.cpp
	Utility.h
)
source_group (Utility FILES ${Utility})

add_library(${PROJECT_NAME} STATIC
	${Headers}
	${SubframeCollector}
	${Utility}
	${Processors}

	${General}
)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC ${COLLECTORS_DIR}
	PUBLIC ${HEADERS_DIR}
	PUBLIC ${PROCESSORS_DIR}
	PUBLIC General
)