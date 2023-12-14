#include "renderer_models_view.h"
namespace Narradia
{
   RendererModelsView::RendererModelsView()
       : timelines_(std::make_shared<std::map<std::string_view, std::map<float, RenderID>>>()) {
      shader_program_view()->Create(vertex_shader_source_models, fragment_shader_source_models);
      location_view_ = GetUniformLocation("view");
      location_projection_ = GetUniformLocation("projection");
      location_alpha_ = GetUniformLocation("mAlpha");
      location_model_ = GetUniformLocation("model");
      location_model_no_translation_ = GetUniformLocation("modelNoTranslation");
      location_color_mod_ = GetUniformLocation("mColorMod");
      location_view_pos_ = GetUniformLocation("viewPos");
      location_fog_color_ = GetUniformLocation("fogColor");
      location_no_fog_ = GetUniformLocation("noFog");
      location_no_lighting_ = GetUniformLocation("noLighting");
   }

   void RendererModelsView::NewModel(std::string_view model_name) {
      auto model = ModelBank::get()->GetModel(model_name);
      model_ids_.insert({model_name.data(), std::map<int, std::map<float, const BodyData>>()});
      auto i_body = 0;
      for (auto &body : *model->model_parts()) {
         auto &timelines = body->timeline()->keyframes;
         for (auto &keyframe : timelines) {
            auto keyframe_time = keyframe.first;
            auto anim_key_body_keyframe = keyframe.second;
            auto vertex_count = anim_key_body_keyframe->vertices.size();
            auto body_keyframe_id = NewBodyKeyframe(model_name, keyframe_time, vertex_count);
            if (model_ids_.at(model_name.data()).count(i_body) == 0)
               model_ids_.at(model_name.data()).insert({i_body, std::map<float, const BodyData>()});
            BodyData body_data;
            body_data.rid = body_keyframe_id;
            body_data.image_name = body->texture_name();
            body_data.num_vertices = vertex_count;
            model_ids_.at(model_name.data()).at(i_body).insert({keyframe_time, body_data});
            auto &model_keyframe = body->timeline()->keyframes.at(keyframe_time);
            std::vector<Vertex3F> vertices;
            std::vector<Point3F> normals;
            auto &anim_vertices = model_keyframe->vertices;
            for (auto v : anim_vertices) {
               Vertex3F v3f;
               v3f.position = v.position;
               v3f.color = v.color;
               v3f.uv = v.uv;
               vertices.push_back(v3f);
               Point3F n3f;
               n3f.x = v.normal.x;
               n3f.y = v.normal.y;
               n3f.z = v.normal.z;
               normals.push_back(n3f);
            }
            NewBodyKeyframeGeometry(
                body->texture_name(), keyframe_time, body_keyframe_id, vertices, normals);
         }
         i_body++;
      }
   }

   void RendererModelsView::DrawModel(
       std::string_view model_name, float ms_time, Point3F position, float rotation, float scaling,
       float brightness, glm::vec3 color_mod, bool no_fog, bool no_lighting) {
      if (model_ids_.count(model_name.data()) == 0)
         return;
      if (!is_batch_drawing_) {
         glEnable(GL_DEPTH_TEST);
         glUseProgram(shader_program_view()->shader_program()->program_id());
         glUniformMatrix4fv(
             location_projection_, 1, GL_FALSE, value_ptr(CameraGL::get()->perspective_matrix()));
         glUniformMatrix4fv(
             location_view_, 1, GL_FALSE, glm::value_ptr(CameraGL::get()->view_matrix()));
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
      glUniformMatrix4fv(location_model_, 1, GL_FALSE, glm::value_ptr(model_matrix));
      glUniformMatrix4fv(
          location_model_no_translation_, 1, GL_FALSE, glm::value_ptr(model_no_translation_matrix));
      glUniform3fv(location_color_mod_, 1, glm::value_ptr(color_mod));
      auto player_space_coord = Player::get()->position().Multiply(kTileSize);
      glm::vec3 viewPos(
          player_space_coord.x,
          player_space_coord.y +
              CalcTileAverageElevation(Player::get()->position().GetXZ().ToIntPoint()),
          player_space_coord.z);
      glUniform3fv(location_view_pos_, 1, glm::value_ptr(viewPos));
      glm::vec3 fogColorGl(kFogColorModels.r, kFogColorModels.g, kFogColorModels.b);
      glUniform3fv(location_fog_color_, 1, glm::value_ptr(fogColorGl));
      glUniform1f(location_alpha_, brightness);
      glUniform1f(location_no_fog_, no_fog ? 1.0f : 0.0f);
      glUniform1f(location_no_lighting_, no_lighting ? 1.0f : 0.0f);
      auto &all_nodes = model_ids_.at(model_name.data());
      auto p_model = ModelBank::get()->GetModel(model_name);
      int ms_time_used;
      if (p_model->anim_duration() == 0)
         ms_time_used = 0;
      else
         ms_time_used =
             static_cast<int>(ms_time * global_animation_speed_) % p_model->anim_duration();
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
      if (!is_batch_drawing_)
         glUseProgram(0);
   }

   void RendererModelsView::StartBatchDrawing() {
      is_batch_drawing_ = true;
      glEnable(GL_DEPTH_TEST);
      glUseProgram(shader_program_view()->shader_program()->program_id());
      glUniformMatrix4fv(
          location_projection_, 1, GL_FALSE, value_ptr(CameraGL::get()->perspective_matrix()));
      glUniformMatrix4fv(
          location_view_, 1, GL_FALSE, glm::value_ptr(CameraGL::get()->view_matrix()));
   }

   void RendererModelsView::StopBatchDrawing() {
      is_batch_drawing_ = false;
   }

   RendererModelsView::~RendererModelsView() {
      CleanupBase();
   }
}
