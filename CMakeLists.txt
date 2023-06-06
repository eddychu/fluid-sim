cmake_minimum_required(VERSION 3.15)

project(fluid CXX C)

add_executable(${PROJECT_NAME} main.cpp)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

# find_package(lodepng CONFIG REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE lodepng)