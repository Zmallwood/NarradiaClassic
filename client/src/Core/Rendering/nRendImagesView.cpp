#include "nRendImagesView.h"
#include "Conf/Const.h"

namespace Narradia {
   nRendImagesView::nRendImagesView() {
      ShaderProgramView()->Create(
          vertex_shader_source_2d_images, fragment_shader_source_2d_images);
   }

   nRendImagesView::~nRendImagesView() {
      if (k_verbose)
         std::cout << "Cleaning up RendImagesView.\n";

      CleanupBase();

      if (k_verbose)
         std::cout << "Cleaning up of RendImagesView finished.\n";
   }
}
