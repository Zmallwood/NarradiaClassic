#include "draw_model.h"
namespace Narradia
{
   auto DrawModel(
       std::string_view model_name, float ms_time, Point3F position, float rotation, float scaling,
       float brightness, glm::vec3 color_mod, bool no_fog, bool no_lighting) -> void {
      auto renderer = RendererModelsView::get();
      auto model_ids = renderer->model_ids();
      auto is_batch_drawing = renderer->is_batch_drawing();
      if (model_ids->count(model_name.data()) == 0)
         return;
      if (!is_batch_drawing) {
         glEnable(GL_DEPTH_TEST);
         glUseProgram(renderer->shader_program_view()->shader_program()->program_id());
         glUniformMatrix4fv(
             renderer->location_projection(), 1, GL_FALSE,
             value_ptr(CameraGL::get()->perspective_matrix()));
         glUniformMatrix4fv(
             renderer->location_view(), 1, GL_FALSE,
             glm::value_ptr(CameraGL::get()->view_matrix()));
      }
      auto model_matrix = glm::rotate(
          glm::scale(
              glm::translate(glm::mat4(1.0), glm::vec3(position.x, position.y, position.z)),
              glm::vec3(scaling, scaling, scaling)),
          glm::radians(rotation), glm::vec3(0, 1, 0));
      auto model_no_translation_matrix = glm::rotate(
          glm::scale(
              glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0)),
              glm::vec3(scaling, scaling, scaling)),
          glm::radians(rotation), glm::vec3(0, 1, 0));
      glUniformMatrix4fv(renderer->location_model(), 1, GL_FALSE, glm::value_ptr(model_matrix));
      glUniformMatrix4fv(
          renderer->location_model_no_translation(), 1, GL_FALSE,
          glm::value_ptr(model_no_translation_matrix));
      glUniform3fv(renderer->location_color_mod(), 1, glm::value_ptr(color_mod));
      auto player_space_coord = Player::get()->position().Multiply(kTileSize);
      glm::vec3 viewPos(
          player_space_coord.x,
          player_space_coord.y +
              CalcTileAverageElevation(Player::get()->position().GetXZ().ToIntPoint()),
          player_space_coord.z);
      glUniform3fv(renderer->location_view_pos(), 1, glm::value_ptr(viewPos));
      glm::vec3 fogColorGl(
          RendererModelsView::kFogColorModels.r, RendererModelsView::kFogColorModels.g,
          RendererModelsView::kFogColorModels.b);
      glUniform3fv(renderer->location_fog_color(), 1, glm::value_ptr(fogColorGl));
      glUniform1f(renderer->location_alpha(), brightness);
      glUniform1f(renderer->location_no_fog(), no_fog ? 1.0f : 0.0f);
      glUniform1f(renderer->location_no_lighting(), no_lighting ? 1.0f : 0.0f);
      auto &all_nodes = model_ids->at(model_name.data());
      auto p_model = ModelBank::get()->GetModel(model_name);
      int ms_time_used;
      if (p_model->anim_duration() == 0)
         ms_time_used = 0;
      else
         ms_time_used = static_cast<int>(ms_time * renderer->global_animation_speed()) %
                        p_model->anim_duration();
      auto &model_data = all_nodes;
      for (auto &entry : all_nodes) {
         auto &timeline = entry.second;
         auto found_time = -1.0f;
         const BodyData *p_body_data = nullptr;
         for (auto &keyframe : timeline) {
            auto time = keyframe.first;
            if (ms_time_used >= time)
               found_time = time;
         }
         auto &body_data = timeline.at(found_time);
         glBindVertexArray(body_data.rid);
         auto image_id = ImageBank::get()->GetImage(body_data.image_name);
         glBindTexture(GL_TEXTURE_2D, image_id);
         glDrawElements(GL_TRIANGLES, body_data.num_vertices, GL_UNSIGNED_INT, NULL);
      }
      glBindVertexArray(0);
      if (!is_batch_drawing)
         glUseProgram(0);
   }
}
