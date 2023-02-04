cmake_minimum_required(VERSION 3.0.0)
project(prelude2 VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR})

add_definitions(-DPL_DEBUG -DPL_VERSION_ALPHA)

add_library(prelude2
    header.h
    util/mem.h util/mem.c
    include/plmem.h src/plmem.c
    include/plregister.h src/plregister.c
    include/plinst.h src/plinst.c
    include/plcodegen.h src/plcodegen.c
    include/opcode.h
    include/pldump.h src/pldump.c
    include/plparser.h src/plparser.c
    include/plengine.h src/plengine.c
    prelude2.h prelude2.c)

add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
