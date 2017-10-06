project(LZ4)

set(CMAKE_BUILD_TYPE Debug)

set(lz4_src
        lz4.c
        lz4frame.c
        lz4hc.c
        xxhash.c
)

add_library(
	lz4 SHARED
	${lz4_src}
)

add_library(
	lz4 STATIC
	${lz4_src}
)

set_property(TARGET lz4 PROPERTY CXX_STANDARD 11)
