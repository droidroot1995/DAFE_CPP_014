
add_executable(vector17test vector17test.cpp)

target_link_libraries(vector17test PUBLIC
    gtest_main
    vector17
)

add_executable(vector18test vector18test.cpp)

target_link_libraries(vector18test PUBLIC
    gtest_main
    vector18
)

add_executable(vector19test vector19test.cpp)

target_link_libraries(vector19test PUBLIC
    gtest_main
    vector19
)