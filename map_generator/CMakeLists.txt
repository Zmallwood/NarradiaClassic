cmake_minimum_required (VERSION 3.0.0)
set(CMAKE_CXX_COMPILER_WORKS 1)
project (NarradiaMapGenerator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "-Wfatal-errors -std=c++20")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

ADD_CUSTOM_TARGET(debug
  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --parallel 4 --target all
  COMMENT "Creating the executable in the debug mode.")

ADD_CUSTOM_TARGET(release
  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --parallel 4 --target all
  COMMENT "Creating the executable in the release mode.")

include_directories("src")

file(GLOB_RECURSE SOURCE_FILES src/**.cpp)

list(FILTER SOURCE_FILES EXCLUDE REGEX ".*inc.cpp$")

set(PCH_FILES
<iostream>
<memory>
<string>
<vector>
<map>
<set>
<functional>
<numeric>
<filesystem>
<fstream>
<algorithm>
<array>
<ranges>
<limits>

<SDL2/SDL.h>
<glm/glm.hpp>
<glm/gtc/matrix_transform.hpp>
<glm/gtc/type_ptr.hpp>
<glm/ext/matrix_projection.hpp>
<glm/gtx/closest_point.hpp>

"src/matter/model/point.h"
"src/matter/model/color.h"
"src/matter/model/point3f.h"

"src/common/system/command/singl_cleanup.h"
"src/common/system/singleton.h"
"src/math/system/tile_calc.h"
"src/math/system/trigonometry.h"
)

add_executable (NarradiaMapGenerator ${SOURCE_FILES})

set_target_properties(NarradiaMapGenerator PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(NarradiaMapGenerator PUBLIC SDL2)

target_precompile_headers(NarradiaMapGenerator PRIVATE ${PCH_FILES})
