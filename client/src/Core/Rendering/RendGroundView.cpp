#include "RendGroundView.h"
#include "Conf/Constants.h"

namespace Narradia {
   RendGroundView::RendGroundView() {
      shader_program_view()->Create(vertex_shader_source_tiles, fragment_shader_source_tiles);

      location_projection_ = GetUniformLocation("projection");
      location_view_ = GetUniformLocation("view");
      location_model_ = GetUniformLocation("model");
      location_alpha_ = GetUniformLocation("mAlpha");
      location_view_pos_ = GetUniformLocation("viewPos");
      location_fog_color_ = GetUniformLocation("fogColor");

      fog_color_ground_ = k_fogColorGround;
   }

   RendGroundView::~RendGroundView() {
      CleanupBase();
   }
}
