cmake_minimum_required(VERSION 3.23)
project(objViewer)

set(CMAKE_CXX_STANDARD 17)

add_executable(objViewer main.cpp SphCoor/SphCoor.cpp SphCoor/SphCoor.h main.h Utility.cpp Utility.h Object/Object.cpp Object/Object.h Vertex/Vertex3.cpp Vertex/Vertex3.h Vertex/Vertex2.cpp Vertex/Vertex2.h)
link_directories(lib)
target_link_libraries(objViewer -lopengl32 -lglu32 -lfreeglut)
