
add_executable(unionFind UnionFindTemplate.cpp)
target_link_libraries(unionFind libUtils)

add_executable(quickFind UnionFindQuickFind.cpp)
target_link_libraries(quickFind libUtils)

add_executable(quickUnion UnionFindQuickUnion.cpp)
target_link_libraries(quickUnion libUtils)

add_executable(weightedQuickUnion UnionFindWeightedQuickUnion.cpp)
target_link_libraries(weightedQuickUnion libUtils)

