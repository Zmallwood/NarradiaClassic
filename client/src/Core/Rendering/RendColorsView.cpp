#include "RendColorsView.h"
#include "Conf/Constants.h"

namespace Narradia {
   RendColorsView::RendColorsView() {
      shader_program_view()->Create(
          vertex_shader_source_2d_solid_colors, fragment_shader_source_2d_solid_colors);
   }

   RendColorsView::~RendColorsView() {
      if (k_verbose)
         std::cout << "Cleaning up DrwSolidColorsV.\n";
      CleanupBase();
      if (k_verbose)
         std::cout << "Cleaning up of DrwSolidColorsV finished.\n";
   }
}
