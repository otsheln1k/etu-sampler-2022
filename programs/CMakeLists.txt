add_executable(empty empty.c)
target_link_libraries(empty sampler)

add_executable(test_cyc test_cyc.c)
target_link_libraries(test_cyc sampler)

add_executable(test_sub test_sub.c)
target_link_libraries(test_sub sampler)

add_executable(simple simple.c)
target_link_libraries(simple sampler)

add_executable(bad bad.c)
target_link_libraries(bad sampler)
