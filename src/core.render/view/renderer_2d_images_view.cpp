#include "renderer_2d_images_view.h"
#include "core.render.shaders/model/2d_images_fragment.inc.cpp"
#include "core.render.shaders/model/2d_images_vertex.inc.cpp"
namespace Narradia {
  /**
   Create the shader program for the provided shader
   sources.
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
