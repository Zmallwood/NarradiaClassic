#if 1
#include "draw_tile.h"
#include "conf.h"
#include "assets.h"
#include "render/camera_gl.h"
#include "render/renderer_tiles_v.h"
#include "actors.h"
#include "math.h"
#endif

namespace Narradia
{
   auto DrawTile(std::string_view image_name, RenderID vao_id, bool depth_test_off) -> void
   {
      auto vertex_count = 4;
      auto renderer = RendererTilesV::get();
      if (depth_test_off)
         glDisable(GL_DEPTH_TEST);
      else
         glEnable(GL_DEPTH_TEST);
      if (!renderer->is_batch_drawing())
      {
         renderer->UseVAOBegin(vao_id);
         glUniformMatrix4fv(
             renderer->location_projection(), 1, GL_FALSE,
             glm::value_ptr(CameraGL::get()->perspective_matrix()));
         glUniformMatrix4fv(
             renderer->location_view(), 1, GL_FALSE,
             glm::value_ptr(CameraGL::get()->view_matrix()));
         glm::mat4 model(1.0);
         glUniformMatrix4fv(renderer->location_model(), 1, GL_FALSE, glm::value_ptr(model));
         glUniform1f(renderer->location_alpha(), 1.0f);
         auto player_pos = Player::get()->position().Multiply(kTileSize);
         glm::vec3 view_pos(
             player_pos.x,
             player_pos.y +
                 CalcTileAverageElevation(Player::get()->position().GetXZ().ToIntPoint()),
             player_pos.z);
         glUniform3fv(renderer->location_view_pos(), 1, glm::value_ptr(view_pos));
         glm::vec3 fog_color_gl(
             RendererTilesV::kFogColorGround.r, RendererTilesV::kFogColorGround.g,
             RendererTilesV::kFogColorGround.b);
         glUniform3fv(renderer->location_fog_color(), 1, glm::value_ptr(fog_color_gl));
      }
      auto image_id = ImageBank::get()->GetImage(image_name);
      glBindTexture(GL_TEXTURE_2D, image_id);
      glBindVertexArray(vao_id);
      glDrawElements(GL_TRIANGLE_FAN, vertex_count, GL_UNSIGNED_INT, NULL);
      glBindVertexArray(0);
      if (!renderer->is_batch_drawing())
         renderer->UseVAOEnd();
   }
}