#include "Renderer2DImagesView.h"
#include "core.assets/model/ImageBank.h"
#include "core.render.shaders/model/2DImagesFragment.inc.cpp"
#include "core.render.shaders/model/2DImagesVertex.inc.cpp"

namespace Narradia {
    /**
     Create the shader program for the provided shader sources.
    */
    Renderer2DImagesView::Renderer2DImagesView() {
        GetShaderProgramView()->Create(vertex_shader_source, fragment_shader_source);
    }

    /**
     Forwarding cleanup command.
    */
    Renderer2DImagesView::~Renderer2DImagesView() {
        CleanupBase();
    }
}
