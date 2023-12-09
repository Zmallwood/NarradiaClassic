#include "Renderer2DSolidColorsView.h"
#include <GL/glew.h>

namespace Narradia {
    /**
     Create the shader program from shader sources.
    */
    Renderer2DSolidColorsView::Renderer2DSolidColorsView() {
        const GLchar *vertex_shader_source =
#include "core.render.shaders/model//2DSolidColorsVertex.inc.cpp"
            ;
        const GLchar *fragment_shader_source =
#include "core.render.shaders/model/2DSolidColorsFragment.inc.cpp"
            ;
        GetShaderProgramView()->Create(vertex_shader_source, fragment_shader_source);
    }

    /**
     Forwarding cleanup command.
    */
    Renderer2DSolidColorsView::~Renderer2DSolidColorsView() { CleanupBase(); }
}
