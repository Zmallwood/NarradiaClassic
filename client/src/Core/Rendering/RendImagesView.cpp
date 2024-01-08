#include "RendImagesView.h"
#include "Conf/Constants.h"

namespace Narradia {
   RendImagesView::RendImagesView() {
      shader_program_view()->Create(
          vertex_shader_source_2d_images, fragment_shader_source_2d_images);
   }

   RendImagesView::~RendImagesView() {
      if (k_verbose)
         std::cout << "Cleaning up RendImagesView.\n";

      CleanupBase();

      if (k_verbose)
         std::cout << "Cleaning up of RendImagesView finished.\n";
   }
}
