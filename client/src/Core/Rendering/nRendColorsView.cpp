#include "nRendColorsView.h"
#include "Conf/Const.h"

namespace Narradia {
   nRendColorsView::nRendColorsView() {
      ShaderProgramView()->Create(
          vertex_shader_source_2d_solid_colors, fragment_shader_source_2d_solid_colors);
   }

   nRendColorsView::~nRendColorsView() {
      if (k_verbose)
         std::cout << "Cleaning up DrwSolidColorsV.\n";
      CleanupBase();
      if (k_verbose)
         std::cout << "Cleaning up of DrwSolidColorsV finished.\n";
   }
}
