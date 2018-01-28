#*****************************************************************************
#                    
#*****************************************************************************
cmake_minimum_required(VERSION 2.6)

project(parse_args)

#*****************************************************************************
#                           ADD CONFIG FILE 
#*****************************************************************************
set(EX_DIR ${CMAKE_SOURCE_DIR}/examples/parse_args)
configure_file(${EX_DIR}/params.cfg 
               ${PROJECT_BINARY_DIR}/params.cfg COPYONLY)

#*****************************************************************************
#                       INCLUDE ANY MACROS HERE 
#*****************************************************************************

include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)
use_cxx11()

#*****************************************************************************
#                   ADD ANY ADDITIONAL PACKAGES HERE 
#*****************************************************************************

set(BOOST_ROOT ~/boost)
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

#*****************************************************************************
#                  SOURCES AND INCLUDE DIRECTORIES
#*****************************************************************************

set(RHD ${CMAKE_SOURCE_DIR}/rhd/include)

set(SOURCES main.cpp)

include_directories(${SOURCE})
include_directories(${RHD})

#*****************************************************************************
#                  ADD EXECUTABLE AND LIBRARIES HERE 
#*****************************************************************************

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES}
                                      -lm)
