#*****************************************************************************
#                    SIMPLE CMAKE FILE FOR SIMPLE STUFF 
#*****************************************************************************
cmake_minimum_required(VERSION 2.6)

project(a)


#*****************************************************************************
#                       INCLUDE ANY MACROS HERE 
#*****************************************************************************

include(cmake/common.cmake)
use_cxx11()


#*****************************************************************************
#                 ADD ANY ADDITIONAL PACKAGES HERE 
#*****************************************************************************

# Use b2 to build boost (see online). 
# These lines assume boost is installed at ~/boost
set(BOOST_ROOT ~/boost)
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})


#*****************************************************************************
#                  SOURCES AND INCLUDE DIRECTORIES
#*****************************************************************************

set(SRC_DIR src)
set(SOURCES ${SRC_DIR}/main.cpp)

set(RHD rhd/include)

include_directories(${SOURCE})
include_directories(${RHD})

#*****************************************************************************
#                  ADD EXECUTABLE AND LIBRARIES HERE 
#*****************************************************************************

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES}
                                      -lm)


