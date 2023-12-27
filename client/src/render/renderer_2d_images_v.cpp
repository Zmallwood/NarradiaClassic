#if 1
#include "renderer_2d_images_v.h"
#include "shaders.h"
#include "render/shader_program_v.h"
#endif

namespace Narradia
{
   Renderer2DImagesV::Renderer2DImagesV()
   {
      shader_program_view()->Create(
          vertex_shader_source_2d_images, fragment_shader_source_2d_images);
   }
   Renderer2DImagesV::~Renderer2DImagesV()
   {
      CleanupBase();
   }
}
