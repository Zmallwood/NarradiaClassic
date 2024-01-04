#if 1
#include "rend_grnd.h"
#include "assets.h"
#include "conf.h"
#include "hero.h"
#include "world.h"
#endif

namespace Narradia
{
   // View
#if 1
   // RendGrndV
#if 1
   RendGrndV::RendGrndV() {

      shader_program_view()->Create(vertex_shader_source_tiles, fragment_shader_source_tiles);

      location_projection_ = GetUniformLocation("projection");
      location_view_ = GetUniformLocation("view");
      location_model_ = GetUniformLocation("model");
      location_alpha_ = GetUniformLocation("mAlpha");
      location_view_pos_ = GetUniformLocation("viewPos");
      location_fog_color_ = GetUniformLocation("fogColor");

      fog_color_ground_ = kFogColorGround;
   }

   RendGrndV::~RendGrndV() {

      CleanupBase();
   }
#endif

   // Free functions
#if 1
   RenderID NewTile() {

      auto num_vertices = 4;
      auto renderer = RendGrndV::get();
      auto renderer_base = renderer->renderer_base();
      auto vertex_array_id = renderer_base->GenNewVAOId();
      auto index_buffer_id = renderer_base->GenNewBufId(BufferTypes::Indices, vertex_array_id);
      auto position_buffer_id =
          renderer_base->GenNewBufId(BufferTypes::Positions3D, vertex_array_id);
      auto color_buffer_id = renderer_base->GenNewBufId(BufferTypes::Colors, vertex_array_id);
      auto uv_buffer_id = renderer_base->GenNewBufId(BufferTypes::Uvs, vertex_array_id);
      auto normal_buffer_id = renderer_base->GenNewBufId(BufferTypes::Normals, vertex_array_id);
      glBindVertexArray(vertex_array_id);
      renderer->SetIndicesData(index_buffer_id, num_vertices, nullptr);
      renderer->SetData(position_buffer_id, num_vertices, nullptr, BufferTypes::Positions3D);
      renderer->SetData(color_buffer_id, num_vertices, nullptr, BufferTypes::Colors);
      renderer->SetData(uv_buffer_id, num_vertices, nullptr, BufferTypes::Uvs);
      renderer->SetData(normal_buffer_id, num_vertices, nullptr, BufferTypes::Normals);
      glBindVertexArray(0);

      return vertex_array_id;
   }

   void SetTileGeom(RenderID vao_id, Square<Vertex3F> &verts) {

      std::vector<Vertex3F> vertices;
      vertices.push_back(verts._00);
      vertices.push_back(verts._10);
      vertices.push_back(verts._11);
      vertices.push_back(verts._01);
      auto renderer = RendGrndV::get();
      auto renderer_base = renderer->renderer_base();

      if (!renderer->is_batch_drawing())
         renderer->UseVAOBegin(vao_id);

      Vec<int> indices(vertices.size());
      std::iota(std::begin(indices), std::end(indices), 0);
      Vec<float> positions;
      Vec<float> colors;
      Vec<float> uvs;
      Vec<float> normals;

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
         auto vertex_normal = vertex.normal;
         normals.push_back(vertex_normal.x);
         normals.push_back(vertex_normal.y);
         normals.push_back(vertex_normal.z);
      }

      auto index_buffer_id = renderer_base->BufId(BufferTypes::Indices, vao_id);
      auto position_buffer_id = renderer_base->BufId(BufferTypes::Positions3D, vao_id);
      auto color_buffer_id = renderer_base->BufId(BufferTypes::Colors, vao_id);
      auto uv_buffer_id = renderer_base->BufId(BufferTypes::Uvs, vao_id);
      auto normal_buffer_id = renderer_base->BufId(BufferTypes::Normals, vao_id);

      glBindVertexArray(vao_id);

      renderer->UpdateIndicesData(index_buffer_id, indices);
      renderer->UpdateData(
          position_buffer_id, positions, BufferTypes::Positions3D, RendGrndV::kLocationPosition);
      renderer->UpdateData(color_buffer_id, colors, BufferTypes::Colors, RendGrndV::kLocationColor);
      renderer->UpdateData(uv_buffer_id, uvs, BufferTypes::Uvs, RendGrndV::kLocationUv);
      renderer->UpdateData(
          normal_buffer_id, normals, BufferTypes::Normals, RendGrndV::kLocationNormal);

      glBindVertexArray(0);

      if (!renderer->is_batch_drawing())
         renderer->UseVAOEnd();
   }


   void StartTileBatchDrawing() {

      auto renderer = RendGrndV::get();
      renderer->set_is_batch_drawing(true);
      glUseProgram(renderer->shader_program_view()->shader_program()->program_id());
      glUniformMatrix4fv(
          renderer->location_projection(), 1, GL_FALSE,
          glm::value_ptr(CameraGL::get()->persp_matrix()));
      glUniformMatrix4fv(
          renderer->location_view(), 1, GL_FALSE, glm::value_ptr(CameraGL::get()->view_matrix()));
      glm::mat4 model(1.0);
      glUniformMatrix4fv(renderer->location_model(), 1, GL_FALSE, glm::value_ptr(model));
      glUniform1f(renderer->location_alpha(), 1.0f);
      auto player_pos = Hero::get()->pos().Multiply(kTileSize);
      auto curr_map_location = Hero::get()->world_location();
      auto map_area = World::get()->CurrWorldArea();
      auto tile_size = kTileSize;
      auto map_offset_x = curr_map_location.x * map_area->Width() * tile_size;
      auto map_offset_y = curr_map_location.y * map_area->Height() * tile_size;
      player_pos.x += map_offset_x;
      player_pos.z += map_offset_y;
      glm::vec3 view_pos(
          player_pos.x,
          player_pos.y +
              CalcTileAverageElevation(
                  Hero::get()->pos().GetXZ().ToIntPoint(), Hero::get()->world_location()),
          player_pos.z);
      glUniform3fv(renderer->location_view_pos(), 1, glm::value_ptr(view_pos));
      glm::vec3 fog_color_gl(
          RendGrndV::get()->fog_color_ground().r, RendGrndV::get()->fog_color_ground().g,
          RendGrndV::get()->fog_color_ground().b);
      glUniform3fv(renderer->location_fog_color(), 1, glm::value_ptr(fog_color_gl));
      glUseProgram(renderer->shader_program_view()->shader_program()->program_id());
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);
   }

   void StopTileBatchDrawing() {

      auto renderer = RendGrndV::get();
      renderer->set_is_batch_drawing(false);
      glUseProgram(0);
      glDisable(GL_CULL_FACE);
   }
#endif
#endif
}
