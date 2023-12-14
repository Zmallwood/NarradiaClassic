/**
 Fragment shader for Renderer2DSolidColors.
*/
#include <GL/glew.h>
inline static const GLchar *fragment_shader_source_2d_solid_colors =
    R"(
    #version 330 core
    precision mediump float;
    in vec4 ex_Color;

    out vec4 fragColor;

    void main() 
    {
        fragColor = ex_Color;
    }
)";
