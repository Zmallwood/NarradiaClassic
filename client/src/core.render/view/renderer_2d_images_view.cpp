#include "renderer_2d_images_view.h"
namespace Narradia
{
   Renderer2DImagesView::Renderer2DImagesView() {
      GetShaderProgramView()->Create(
          vertex_shader_source_2d_images, fragment_shader_source_2d_images);
   }

   Renderer2DImagesView::~Renderer2DImagesView() {
      CleanupBase();
   }
}
