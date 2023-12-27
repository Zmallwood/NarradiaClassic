#if 1
#include "renderer_2d_solid_colors_v.h"
#include "shaders.h"
#include "render/shader_program_v.h"
#endif

namespace Narradia
{
   Renderer2DSolidColorsV::Renderer2DSolidColorsV()
   {
      shader_program_view()->Create(
          vertex_shader_source_2d_solid_colors, fragment_shader_source_2d_solid_colors);
   }
   Renderer2DSolidColorsV::~Renderer2DSolidColorsV()
   {
      CleanupBase();
   }
}
