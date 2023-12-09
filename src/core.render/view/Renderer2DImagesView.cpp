#include "Renderer2DImagesView.h"
#include "core.assets/model/ImageBank.h"
#include <GL/glew.h>

namespace Narradia {
    /**
     Create the shader program for the provided shader sources.
    */
    Renderer2DImagesView::Renderer2DImagesView() {
        const GLchar *vertex_shader_source =
#include "core.render.shaders/model/2DImagesVertex.inc.cpp"
            ;
        const GLchar *fragment_shader_source =
#include "core.render.shaders/model/2DImagesFragment.inc.cpp"
            ;
        GetShaderProgramView()->Create(vertex_shader_source, fragment_shader_source);
    }

    /**
     Forwarding cleanup command.
    */
    Renderer2DImagesView::~Renderer2DImagesView() { CleanupBase(); }
}
