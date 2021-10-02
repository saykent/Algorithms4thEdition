
add_subdirectory(exercises)

add_executable(bag bag.cpp)
target_link_libraries(bag libUtils)

add_executable(evaluate Evaluate.cpp)
target_link_libraries(evaluate libUtils)

add_executable(fixedCapacityStackOfStrings FixedCapacityStackOfStrings.cpp)
target_link_libraries(fixedCapacityStackOfStrings libUtils)

add_executable(fixedCapacityStack FixedCapacityStack.cpp)
target_link_libraries(fixedCapacityStack libUtils)

add_executable(resizingArrayStack ResizingArrayStack.cpp)
target_link_libraries(resizingArrayStack libUtils)

add_executable(stack Stack.cpp)
target_link_libraries(stack libUtils)

add_executable(queue Queue.cpp)
target_link_libraries(queue libUtils)

add_executable(bagLinkedList BagLinkedList.cpp)
target_link_libraries(bagLinkedList libUtils)

