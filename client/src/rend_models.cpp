#if 1
#include "rend_models.h"
#include "assets.h"
#include "calc.h"
#include "conf.h"
#include "hero.h"
#include "world.h"
#endif

namespace Narradia
{
   // View
#if 1
   // RendModelsV
#if 1
   RendModelsV::RendModelsV()
       : timelines_(std::make_shared<std::map<std::string_view, std::map<float, RenderID>>>()),
         model_ids_(std::make_shared<
                    std::map<std::string, std::map<int, std::map<float, const BodyData>>>>()) {
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
   RendModelsV::~RendModelsV() {
      if (kVerbose)
         std::cout << "Cleaning up RendModelsV.\n";
      CleanupBase();
      if (kVerbose)
         std::cout << "Cleaning up of RendModelsV finished.\n";
   }
   auto RendModelsV::NewBodyKeyframe(std::string_view model_name, float ms_time) -> RenderID {
      auto vao_id = renderer_base_->GenNewVAOId();
      if (timelines_->count(model_name) == 0)
         timelines_->insert({model_name, std::map<float, RenderID>()});
      timelines_->at(model_name).insert({ms_time, vao_id});
      return vao_id;
   }
   auto RendModelsV::NewBodyKeyframeGeometry(
       GLuint vao_id, std::vector<Vertex3F> vertices, std::vector<Point3F> vertex_normals) -> void {
      glEnable(GL_DEPTH_TEST);
      UseVAOBegin(vao_id);
      glUniformMatrix4fv(
          location_projection_, 1, GL_FALSE, value_ptr(CameraGL::get()->persp_matrix()));
      glUniformMatrix4fv(location_view_, 1, GL_FALSE, value_ptr(CameraGL::get()->view_matrix()));
      glUniform1f(location_alpha_, 1.0f);
      std::vector<int> indices(vertices.size());
      std::iota(std::begin(indices), std::end(indices), 0);
      std::vector<float> positions;
      std::vector<float> colors;
      std::vector<float> uvs;
      std::vector<float> normals;
      auto i = 0;
      for (auto &vertex : vertices) {
         positions.push_back(vertex.pos.x);
         positions.push_back(vertex.pos.y);
         positions.push_back(vertex.pos.z);
         colors.push_back(vertex.color.r);
         colors.push_back(vertex.color.g);
         colors.push_back(vertex.color.b);
         colors.push_back(vertex.color.a);
         uvs.push_back(vertex.uv.x);
         uvs.push_back(vertex.uv.y);
         if (vertex_normals.size() > i) {
            auto vertex_normal = vertex_normals.at(i);
            normals.push_back(vertex_normal.x);
            normals.push_back(-vertex_normal.y);
            normals.push_back(vertex_normal.z);
         }
         i++;
      }
      auto index_buffer_id = renderer_base_->GenNewBufId(BufferTypes::Indices, vao_id);
      auto position_buffer_id = renderer_base_->GenNewBufId(BufferTypes::Positions3D, vao_id);
      auto color_buffer_id = renderer_base_->GenNewBufId(BufferTypes::Colors, vao_id);
      auto uv_buffer_id = renderer_base_->GenNewBufId(BufferTypes::Uvs, vao_id);
      auto normal_buffer_id = renderer_base_->GenNewBufId(BufferTypes::Normals, vao_id);
      auto num_vertices = vertices.size();
      SetIndicesData(index_buffer_id, num_vertices, indices.data());
      SetData(
          position_buffer_id, num_vertices, positions.data(), BufferTypes::Positions3D,
          RendModelsV::kLocationPosition);
      SetData(
          color_buffer_id, num_vertices, colors.data(), BufferTypes::Colors,
          RendModelsV::kLocationColor);
      SetData(uv_buffer_id, num_vertices, uvs.data(), BufferTypes::Uvs, RendModelsV::kLocationUv);
      SetData(
          normal_buffer_id, num_vertices, normals.data(), BufferTypes::Normals,
          RendModelsV::kLocationNormal);
      UseVAOEnd();
   }
#endif

   // Free functions
#if 1
   auto NewModel(std::string_view model_name) -> void {
      auto renderer = RendModelsV::get();
      auto model = ModelBank::get()->GetModel(model_name);
      auto model_ids = renderer->model_ids();
      model_ids->insert({model_name.data(), std::map<int, std::map<float, const BodyData>>()});
      auto i_body = 0;
      for (auto &body : *model->model_parts()) {
         auto &timelines = body->timeline()->keyframes;
         for (auto &keyframe : timelines) {
            auto keyframe_time = keyframe.first;
            auto anim_key_body_keyframe = keyframe.second;
            auto vertex_count = anim_key_body_keyframe->vertices.size();
            auto body_keyframe_id = RendModelsV::get()->NewBodyKeyframe(model_name, keyframe_time);
            if (model_ids->at(model_name.data()).count(i_body) == 0)
               model_ids->at(model_name.data()).insert({i_body, std::map<float, const BodyData>()});
            BodyData body_data;
            body_data.rid = body_keyframe_id;
            body_data.image_name = body->texture_name();
            body_data.num_vertices = vertex_count;
            model_ids->at(model_name.data()).at(i_body).insert({keyframe_time, body_data});
            auto &model_keyframe = body->timeline()->keyframes.at(keyframe_time);
            std::vector<Vertex3F> vertices;
            std::vector<Point3F> normals;
            auto &anim_vertices = model_keyframe->vertices;
            for (auto v : anim_vertices) {
               Vertex3F v3f;
               v3f.pos = v.pos;
               v3f.color = v.color;
               v3f.uv = v.uv;
               vertices.push_back(v3f);
               Point3F n3f;
               n3f.x = v.normal.x;
               n3f.y = v.normal.y;
               n3f.z = v.normal.z;
               normals.push_back(n3f);
            }
            RendModelsV::get()->NewBodyKeyframeGeometry(body_keyframe_id, vertices, normals);
         }
         i_body++;
      }
   }
   auto DrawModel(
       std::string_view model_name, float ms_time, Point3F position, float rotation, float scaling,
       float brightness, glm::vec3 color_mod, bool no_fog, bool no_lighting) -> void {
      auto renderer = RendModelsV::get();
      auto model_ids = renderer->model_ids();
      auto is_batch_drawing = renderer->is_batch_drawing();
      if (model_ids->count(model_name.data()) == 0)
         return;
      if (!is_batch_drawing) {
         glEnable(GL_DEPTH_TEST);
         glUseProgram(renderer->shader_program_view()->shader_program()->program_id());
         glUniformMatrix4fv(
             renderer->location_projection(), 1, GL_FALSE,
             value_ptr(CameraGL::get()->persp_matrix()));
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
      auto player_space_coord = Hero::get()->pos().Multiply(kTileSize);

      auto curr_map_location = Hero::get()->world_location();
      auto map_area = World::get()->CurrWorldArea();
      auto tile_size = kTileSize;
      auto map_offset_x = curr_map_location.x * map_area->Width() * tile_size;
      auto map_offset_y = curr_map_location.y * map_area->Height() * tile_size;
      player_space_coord.x += map_offset_x;
      player_space_coord.z += map_offset_y;
      glm::vec3 viewPos(
          player_space_coord.x,
          player_space_coord.y +
              CalcTileAverageElevation(Hero::get()->pos().GetXZ().ToIntPoint()),
          player_space_coord.z);
      glUniform3fv(renderer->location_view_pos(), 1, glm::value_ptr(viewPos));
      glm::vec3 fogColorGl(
          RendModelsV::kFogColorModels.r, RendModelsV::kFogColorModels.g,
          RendModelsV::kFogColorModels.b);
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
   auto StartModelsBatchDrawing() -> void {
      auto renderer = RendModelsV::get();
      renderer->set_is_batch_drawing(true);
      glEnable(GL_DEPTH_TEST);
      glUseProgram(renderer->shader_program_view()->shader_program()->program_id());
      glUniformMatrix4fv(
          renderer->location_projection(), 1, GL_FALSE, value_ptr(CameraGL::get()->persp_matrix()));
      glUniformMatrix4fv(
          renderer->location_view(), 1, GL_FALSE, glm::value_ptr(CameraGL::get()->view_matrix()));
   }
   auto StopModelsBatchDrawing() -> void {
      auto renderer = RendModelsV::get();
      renderer->set_is_batch_drawing(false);
   }
#endif
#endif
}
