#include "start_tile_batch_drawing.h"
namespace Narradia
{
   auto StartTileBatchDrawing() -> void {
      auto renderer = RendererTilesView::get();
      renderer->set_is_batch_drawing(true);
      glUseProgram(renderer->GetShaderProgramView()->shader_program()->program_id());
      glUniformMatrix4fv(
          renderer->location_projection(), 1, GL_FALSE,
          glm::value_ptr(CameraGL::get()->perspective_matrix()));
      glUniformMatrix4fv(
          renderer->location_view(), 1, GL_FALSE, glm::value_ptr(CameraGL::get()->view_matrix()));
      glm::mat4 model(1.0);
      glUniformMatrix4fv(renderer->location_model(), 1, GL_FALSE, glm::value_ptr(model));
      glUniform1f(renderer->location_alpha(), 1.0f);
      auto player_pos = Player::get()->position().Multiply(kTileSize);
      glm::vec3 view_pos(
          player_pos.x,
          player_pos.y + CalcTileAverageElevation(Player::get()->position().GetXZ().ToIntPoint()),
          player_pos.z);
      glUniform3fv(renderer->location_view_pos(), 1, glm::value_ptr(view_pos));
      glm::vec3 fog_color_gl(
          RendererTilesView::kFogColorGround.r, RendererTilesView::kFogColorGround.g,
          RendererTilesView::kFogColorGround.b);
      glUniform3fv(renderer->location_fog_color(), 1, glm::value_ptr(fog_color_gl));
      glUseProgram(renderer->GetShaderProgramView()->shader_program()->program_id());
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);
   }
}
