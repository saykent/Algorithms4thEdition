
add_executable(selection Selection.cpp)
target_link_libraries(selection libUtils)

add_executable(insertion Insertion.cpp)
target_link_libraries(insertion libUtils)

add_executable(sortCompare SortCompare.cpp)
target_link_libraries(sortCompare libUtils)
