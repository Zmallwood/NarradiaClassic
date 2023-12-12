#include "renderer_2d_solid_colors_view.h"
#include "core.render.shaders/model/2d_solid_colors_fragment.inc.cpp"
#include "core.render.shaders/model/2d_solid_colors_vertex.inc.cpp"
namespace Narradia
{
    /**
     Create the shader program from shader sources.
    */
    Renderer2DSolidColorsView::Renderer2DSolidColorsView() {
        GetShaderProgramView()->Create(vertex_shader_source, fragment_shader_source);
    }

    /**
     Forwarding cleanup command.
    */
    Renderer2DSolidColorsView::~Renderer2DSolidColorsView() {
        CleanupBase();
    }
}
