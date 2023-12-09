#include "Renderer2DSolidColorsView.h"
#include "core.render.shaders/model//2DSolidColorsVertex.inc.cpp"
#include "core.render.shaders/model/2DSolidColorsFragment.inc.cpp"

namespace Narradia {
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
