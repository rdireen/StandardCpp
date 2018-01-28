#*****************************************************************************
#                    
#*****************************************************************************
cmake_minimum_required(VERSION 2.6)

project(format_text)

#*****************************************************************************
#                       INCLUDE ANY MACROS HERE 
#*****************************************************************************

include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)
use_cxx11()

#*****************************************************************************
#                   ADD ANY ADDITIONAL PACKAGES HERE 
#*****************************************************************************

set(BOOST_ROOT ~/boost)
find_package(Boost)
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
