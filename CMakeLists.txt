cmake_minimum_required(VERSION 3.0.0)
project(project3 VERSION 0.1.0)

include(CTest)
enable_testing()    

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(displayvideo displayvideo.cpp threshold.cpp threshold.h morphological.cpp morphological.h segment.cpp segment.h)
add_executable(displayimage displayimage.cpp threshold.cpp threshold.h morphological.cpp morphological.h segment.cpp segment.h)
add_executable(imgui threshold.cpp threshold.h morphological.cpp morphological.h imgui.cpp cvui.h segment.cpp segment.h)
add_executable(libmorph libmorph.cpp morphological.h morphological.cpp)

target_link_libraries( displayvideo ${OpenCV_LIBS} )
target_link_libraries( displayimage ${OpenCV_LIBS} )
target_link_libraries( libmorph ${OpenCV_LIBS} )
target_link_libraries( imgui ${OpenCV_LIBS} )



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)