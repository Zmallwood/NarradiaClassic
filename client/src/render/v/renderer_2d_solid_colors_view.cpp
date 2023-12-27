#if 1
#include "renderer_2d_solid_colors_view.h"
#include "shaders/m/2d_solid_colors_fragment.inc.cpp"
#include "shaders/m/2d_solid_colors_vertex.inc.cpp"
#include "render/v/shader_program_view.h"
#endif

namespace Narradia
{
   Renderer2DSolidColorsView::Renderer2DSolidColorsView()
   {
      shader_program_view()->Create(
          vertex_shader_source_2d_solid_colors, fragment_shader_source_2d_solid_colors);
   }

   Renderer2DSolidColorsView::~Renderer2DSolidColorsView()
   {
      CleanupBase();
   }
}
