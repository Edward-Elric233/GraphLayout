cmake_minimum_required(VERSION 3.21)
project(GraphLayout)

set(CMAKE_CXX_STANDARD 14)
set(srcPath /home/edward/Software/OGDF/OGDF)
set(buildPath /home/edward/Software/OGDF/OGDF)

include_directories(${srcPath}/include)

add_executable(GraphLayout main.cpp GraphLayout.cpp GraphLayout.h KCoreLayout.cpp KCoreLayout.h Vertex.cpp Vertex.h utils.h Component.cpp Component.h Param.cpp Param.h Singleton.h Shell.cpp Shell.h utils.cpp)

target_link_libraries(GraphLayout pthread)
target_link_libraries(GraphLayout ${buildPath}/libOGDF.a ${buildPath}/libCOIN.a)