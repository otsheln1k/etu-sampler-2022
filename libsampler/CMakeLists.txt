add_library(sampler STATIC
  sampler.c
)

target_include_directories(sampler
  PUBLIC .
)

target_compile_definitions(sampler
  PUBLIC -D_POSIX_C_SOURCE=199309L
)

target_link_libraries(sampler
  -lrt
)
