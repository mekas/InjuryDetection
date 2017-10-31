cmake_minimum_required(VERSION 3.5)
project(tissue_cell)

set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED)
find_package( Boost COMPONENTS system filesystem REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp IoUtil.h IoUtil.cpp Util.cpp Util.h ImgUtil.cpp ImgUtil.h)
add_executable(tissue_cell ${SOURCE_FILES})
target_link_libraries( tissue_cell ${OpenCV_LIBS} ${Boost_LIBRARIES} )