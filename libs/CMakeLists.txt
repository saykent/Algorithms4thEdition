add_library(libUtils "")

target_sources(libUtils
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Scanner.h
    ${CMAKE_CURRENT_LIST_DIR}/In.h
    ${CMAKE_CURRENT_LIST_DIR}/StdIn.h
    ${CMAKE_CURRENT_LIST_DIR}/Date.h
    ${CMAKE_CURRENT_LIST_DIR}/Transaction.h
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Scanner.cpp
    ${CMAKE_CURRENT_LIST_DIR}/StdIn.cpp
    )

target_include_directories(libUtils
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )