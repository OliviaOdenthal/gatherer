cmake_minimum_required (VERSION 3.10)

project(gatherer)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(GATHERER_MAJOR_VERSION 0)
set(GATHERER_MINOR_VERSION 1)
set(GATHERER_VERSION ${GATHERER_MAJOR_VERSION}.${GATHERER_MINOR_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(MATH_INCLUDE "deps/math/include")

set(JSON_INCLUDE "deps/json/single_include/nlohmann")

set(IMGUI_DIR "deps/imgui")
set(IMGUI_INCLUDE 
  "${IMGUI_DIR}"
  "${IMGUI_DIR}/backends"
)
set(IMGUI_SRCS
  "${IMGUI_DIR}/imgui_draw.cpp"
  "${IMGUI_DIR}/imgui_widgets.cpp"
  "${IMGUI_DIR}/imgui.cpp"
  "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
  "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)

find_package(OpenGL REQUIRED)
add_subdirectory(deps/glad)
set(GLAD_DIR "deps/glad")
set(GLAD_INCLUDE
  "${GLAD_DIR}/include/"
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/glfw)

set(GATHERER_CLIENT_SOURCES 
  src/client/utils.cpp
  src/client/gathereddata.cpp
  src/client/imagerenderer.cpp
  src/client/pathsrenderer.cpp
  src/client/axesvisualizer.cpp
  src/client/scenerenderer.cpp
  src/client/filtermanager.cpp
  src/client/spherefilter.cpp
  src/client/windowfilter.cpp
  src/client/application.cpp
  src/client/client.cpp
  ${IMGUI_SRCS}
)

set(EXECUTABLE_CLIENT ${PROJECT_NAME}_client)
add_executable(${EXECUTABLE_CLIENT} ${GATHERER_CLIENT_SOURCES})
set_target_properties(${EXECUTABLE_CLIENT} PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
)
target_include_directories(${EXECUTABLE_CLIENT}
PRIVATE
  "include/"
  ${MATH_INCLUDE}
  ${JSON_INCLUDE}
  ${IMGUI_INCLUDE}
  ${GLAD_INCLUDE}
)
target_link_libraries(${EXECUTABLE_CLIENT}
PUBLIC
  glad
  glfw
  OpenGL::GL
)
