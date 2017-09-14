cmake_minimum_required(VERSION 3.8)
project(bullet_collision)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MyDebugDrawer.h)


find_package(Bullet REQUIRED)
find_package(OpenGL)
find_package(GLUT REQUIRED)

include_directories(${BULLET_INCLUDE_DIRS})
include_directories(./GLUS)
add_executable(bullet_collision ${SOURCE_FILES})

add_executable(example example.cpp)

target_link_libraries(example
        ${BULLET_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES})
target_link_libraries(bullet_collision
        ${BULLET_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES})