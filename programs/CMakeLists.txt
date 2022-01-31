add_executable(empty empty.c)
target_link_libraries(empty sampler)

add_executable(test_cyc test_cyc.c)
target_link_libraries(test_cyc sampler)

add_executable(test_sub test_sub.c)
target_link_libraries(test_sub sampler)

add_executable(test_bubble test_bubble.c)
target_link_libraries(test_bubble sampler)

add_executable(test_bubble2 test_bubble2.c)
target_link_libraries(test_bubble2 sampler)

add_executable(inttrapez-1full inttrapez-1full.c)
target_link_libraries(inttrapez-1full sampler)

add_executable(inttrapez-1part inttrapez-1part.c)
target_link_libraries(inttrapez-1part sampler)

add_executable(inttrapez-2full inttrapez-2full.c)
target_link_libraries(inttrapez-2full sampler)

add_executable(inttrapez-2part inttrapez-2part.c)
target_link_libraries(inttrapez-2part sampler)
