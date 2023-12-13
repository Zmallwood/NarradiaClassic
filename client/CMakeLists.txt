cmake_minimum_required (VERSION 3.0.0)
set(CMAKE_CXX_COMPILER_WORKS 1)
project (NarradiaClassic)

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
<SDL2/SDL_image.h>
<SDL2/SDL_ttf.h>
<GL/glew.h>
<glm/glm.hpp>
<glm/gtc/matrix_transform.hpp>
<glm/gtc/type_ptr.hpp>
<glm/ext/matrix_projection.hpp>
<glm/gtx/closest_point.hpp>
<assimp/Importer.hpp>
<assimp/scene.h>
<assimp/postprocess.h>

"src/matter/model/size.h"
"src/matter/model/sizef.h"
"src/matter/model/color.h"
"src/matter/model/colors.h"
"src/matter/model/rectf.h"
"src/matter/model/point.h"
"src/matter/model/pointf.h"
"src/matter/model/point3f.h"
"src/matter/model/gl_rectf.h"
"src/matter/model/vertex2f.h"
"src/matter/model/vertex3f.h"

"src/common/system/command/singletons_cleanup.h"
"src/common/system/command/utilities.h"
"src/common/system/command/canvas_utilities.h"
"src/common/system/singleton.h"
"src/common/system/typedefs.h"
"src/core/model/sdl_deleter.h"
"src/math/system/trigonometry.h"
"src/math/system/exp_calc.h"
"src/math/system/tile_calc.h"
)

add_executable (NarradiaClassic ${SOURCE_FILES})

set_target_properties(NarradiaClassic PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(NarradiaClassic PUBLIC SDL2 SDL2_image SDL2_ttf GL GLEW assimp)

target_precompile_headers(NarradiaClassic PRIVATE ${PCH_FILES})