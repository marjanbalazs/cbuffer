set(HEADER_LIST "${cbuffer_SOURCE_DIR}/include/cbuffer.h")

add_library(cbuffer cbuffer.c ${HEADER_LIST})
target_include_directories(cbuffer PUBLIC ../include)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
