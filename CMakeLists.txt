cmake_minimum_required(VERSION 3.10)
project(black_hole)

set(CMAKE_BUILD Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CSS_FLAGS} -Wall -std=c++17")
#set(CMAKE_CXX_FLAGS "${CMAKE_CSS_FLAGS} -Wall -Werror -std=c++17")
set(source_dir "${PROJECT_SOURCE_DIR}/src/")
set(project_dir "${CMAKE_CURRENT_SOURCE_DIR}/")
file(GLOB source_files "${source_dir}/*.cpp"
                        "${source_dir}/vendor/stb_image/*.cpp")

set(FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

add_executable(${PROJECT_NAME} ${source_files})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        OpenGL::GL
        GLEW::GLEW
        glfw
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc
                            ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor/stb_image)