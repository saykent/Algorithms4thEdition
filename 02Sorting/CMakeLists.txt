add_subdirectory(2.1ElementarySorts)
add_subdirectory(2.2Mergesort)
add_subdirectory(2.3QuickSort)

add_executable(sortCompare SortCompare.cpp)
target_link_libraries(sortCompare libUtils)
