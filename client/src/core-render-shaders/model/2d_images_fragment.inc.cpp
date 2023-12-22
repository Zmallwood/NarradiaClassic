////////////////////////////////////////////////////////////////////////////////
/// Fragment shader for Renderer2DImages.
////////////////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
inline static const GLchar *fragment_shader_source_2d_images =
    R"(
    #version 330 core
    precision mediump float;
    
    in vec4 ex_Color;
    in vec2 ex_TexCoord;
    uniform sampler2D TexUnit;

    out vec4 fragColor;

    void main()
    {
        vec4 texColor = texture(TexUnit, ex_TexCoord);
        fragColor = ex_Color*0.0 + texColor;
    }
)";
