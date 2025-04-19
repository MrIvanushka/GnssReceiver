project(Math)

set ( SLAE
	DenseMatrix.h
	Overloads.h
)
source_group (SLAE FILES ${SLAE})

add_library(${PROJECT_NAME} STATIC
	Vector3.h
	Vector3.cpp

	${SLAE}
)


target_include_directories(${PROJECT_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC CommonUtilities
)