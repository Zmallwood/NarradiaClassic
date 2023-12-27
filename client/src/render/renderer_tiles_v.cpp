#if 1
#include "renderer_tiles_v.h"
#include "shaders.h"
#include "render/shader_program_v.h"
#endif

namespace Narradia
{
   RendererTilesV::RendererTilesV()
   {
      shader_program_view()->Create(vertex_shader_source_tiles, fragment_shader_source_tiles);
      location_projection_ = GetUniformLocation("projection");
      location_view_ = GetUniformLocation("view");
      location_model_ = GetUniformLocation("model");
      location_alpha_ = GetUniformLocation("mAlpha");
      location_view_pos_ = GetUniformLocation("viewPos");
      location_fog_color_ = GetUniformLocation("fogColor");
   }
   RendererTilesV::~RendererTilesV()
   {
      CleanupBase();
   }
}
