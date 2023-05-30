cmake_minimum_required(VERSION 3.26.0)
project(MyProject)

find_package(IhorGUI REQUIRED)
find_package (glfw3 3.2 REQUIRED)
find_package (GLEW REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)

add_executable(MyProject main.cpp)


target_link_libraries(MyProject IhorGUI)
target_link_libraries (MyProject glfw)
target_link_libraries (MyProject GLEW)
target_link_libraries(MyProject OpenGL)
target_link_libraries(MyProject glut)