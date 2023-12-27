#if 1
#include "renderer_2d_images_view.h"
#include "shaders/m/2d_images_fragment.inc.cpp"
#include "shaders/m/2d_images_vertex.inc.cpp"
#include "render/v/shader_program_view.h"
#endif

namespace Narradia
{
   Renderer2DImagesView::Renderer2DImagesView()
   {
      shader_program_view()->Create(
          vertex_shader_source_2d_images, fragment_shader_source_2d_images);
   }

   Renderer2DImagesView::~Renderer2DImagesView()
   {
      CleanupBase();
   }
}
