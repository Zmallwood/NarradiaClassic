#include "renderer_tiles_view.h"
#include "core-render-shaders/model/tiles_fragment.inc.cpp"
#include "core-render-shaders/model/tiles_vertex.inc.cpp"
namespace Narradia
{
   RendererTilesView::RendererTilesView() {
      shader_program_view()->Create(vertex_shader_source_tiles, fragment_shader_source_tiles);
      location_projection_ = GetUniformLocation("projection");
      location_view_ = GetUniformLocation("view");
      location_model_ = GetUniformLocation("model");
      location_alpha_ = GetUniformLocation("mAlpha");
      location_view_pos_ = GetUniformLocation("viewPos");
      location_fog_color_ = GetUniformLocation("fogColor");
   }

   RendererTilesView::~RendererTilesView() {
      CleanupBase();
   }
}
