include_directories(../)
add_executable(01 01.c)
target_link_libraries(01 prelude2)
add_test(01_test 01)