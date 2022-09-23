cmake_minimum_required(VERSION 3.23)
project(objViewer)

set(CMAKE_CXX_STANDARD 17)

add_executable(objViewer main.cpp SphCoor/SphCoor.cpp SphCoor/SphCoor.h main.h Utility.cpp Utility.h Object/Object.cpp Object/Object.h Vector/Vector3.cpp Vector/Vector3.h Vector/Vector2.cpp Vector/Vector2.h Object/Transform/Transform.cpp Object/Transform/Transform.h)
link_directories(lib)
target_link_libraries(objViewer -lopengl32 -lglu32 -lfreeglut)
