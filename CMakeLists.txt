project(meteoplots)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

find_package(ROOT REQUIRED COMPONENTS Hist Gpad Graf MathCore)

include(${ROOT_USE_FILE})

add_executable(meteoplots main.cpp meteoPlots.cpp)

target_link_libraries(meteoplots ${ROOT_LIBRARIES})