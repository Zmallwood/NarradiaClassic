#if 1
#include "start_tile_batch_drawing.h"
#include "conf/consts.h"
#include "world-actors/player.h"
#include "render/camera_gl.h"
#include "render/renderer_tiles_v.h"
#include "world-struct.h"
#include "render/shader_program_v.h"
#include "render/shader_program.h"
#endif

namespace Narradia
{
   auto StartTileBatchDrawing() -> void
   {
      auto renderer = RendererTilesV::get();
      renderer->set_is_batch_drawing(true);
      glUseProgram(renderer->shader_program_view()->shader_program()->program_id());
      glUniformMatrix4fv(
          renderer->location_projection(), 1, GL_FALSE,
          glm::value_ptr(CameraGL::get()->perspective_matrix()));
      glUniformMatrix4fv(
          renderer->location_view(), 1, GL_FALSE, glm::value_ptr(CameraGL::get()->view_matrix()));
      glm::mat4 model(1.0);
      glUniformMatrix4fv(renderer->location_model(), 1, GL_FALSE, glm::value_ptr(model));
      glUniform1f(renderer->location_alpha(), 1.0f);
      auto player_pos = Player::get()->position().Multiply(kTileSize);
      auto curr_map_location = Player::get()->world_location();
      auto map_area = World::get()->CurrMapArea();
      auto tile_size = kTileSize;
      auto map_offset_x = curr_map_location.x * map_area->GetWidth() * tile_size;
      auto map_offset_y = curr_map_location.y * map_area->GetHeight() * tile_size;
      player_pos.x += map_offset_x;
      player_pos.z += map_offset_y;
      glm::vec3 view_pos(
          player_pos.x,
          player_pos.y + CalcTileAverageElevation(Player::get()->position().GetXZ().ToIntPoint()),
          player_pos.z);
      glUniform3fv(renderer->location_view_pos(), 1, glm::value_ptr(view_pos));
      glm::vec3 fog_color_gl(
          RendererTilesV::kFogColorGround.r, RendererTilesV::kFogColorGround.g,
          RendererTilesV::kFogColorGround.b);
      glUniform3fv(renderer->location_fog_color(), 1, glm::value_ptr(fog_color_gl));
      glUseProgram(renderer->shader_program_view()->shader_program()->program_id());
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);
   }
}
