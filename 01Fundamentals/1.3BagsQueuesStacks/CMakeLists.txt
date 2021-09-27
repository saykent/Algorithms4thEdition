add_executable(bag bag.cpp)
target_link_libraries(bag libUtils)

add_executable(evaluate Evaluate.cpp)
target_link_libraries(evaluate libUtils)
