#include "renderer_tiles_view.h"
#include "camera_gl.h"
#include "core.assets/model/image_bank.h"
#include "core.render.shaders/model/tiles_fragment.inc.cpp"
#include "core.render.shaders/model/tiles_vertex.inc.cpp"
#include "world.actors/model/player.h"

namespace Narradia {
  RendererTilesView::RendererTilesView() {
    GetShaderProgramView()->Create(vertex_shader_source, fragment_shader_source);
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
