#include "renderer_2d_solid_colors_view.h"
namespace Narradia
{
   Renderer2DSolidColorsView::Renderer2DSolidColorsView() {
      shader_program_view()->Create(
          vertex_shader_source_2d_solid_colors, fragment_shader_source_2d_solid_colors);
   }

   Renderer2DSolidColorsView::~Renderer2DSolidColorsView() {
      CleanupBase();
   }
}
