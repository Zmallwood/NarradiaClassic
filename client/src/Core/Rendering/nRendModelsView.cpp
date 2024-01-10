#include "nRendModelsView.h"
#include "RenderingCore.h"
#include "Conf/Const.h"

namespace Narradia {
   nRendModelsView::nRendModelsView()
       : timelines_(MakeShared<Map<StringView, Map<float, RenderID>>>()),
         model_ids_(MakeShared<Map<String, Map<int, Map<float, const nBodyData>>>>()) {
      ShaderProgramView()->Create(vertex_shader_source_models, fragment_shader_source_models);

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

      fog_color_models_ = k_fogColorModels;
   }

   nRendModelsView::~nRendModelsView() {
      if (k_verbose)
         std::cout << "Cleaning up RendModelsV.\n";

      CleanupBase();

      if (k_verbose)
         std::cout << "Cleaning up of RendModelsV finished.\n";
   }

   RenderID nRendModelsView::NewBodyKeyframe(StringView model_name, float ms_time) {
      auto vao_id = m_rendererBase->GenNewVAOId();

      if (timelines_->count(model_name) == 0)
         timelines_->insert({model_name, Map<float, RenderID>()});

      timelines_->at(model_name).insert({ms_time, vao_id});

      return vao_id;
   }

   void nRendModelsView::NewBodyKeyframeGeometry(
       GLuint vao_id, Vec<Vertex3F> vertices, Vec<Point3F> vertex_normals) {
      glEnable(GL_DEPTH_TEST);
      UseVAOBegin(vao_id);
      glUniformMatrix4fv(
          location_projection_, 1, GL_FALSE, value_ptr(nCameraGL::get()->PerspMatrix()));
      glUniformMatrix4fv(location_view_, 1, GL_FALSE, value_ptr(nCameraGL::get()->ViewMatrix()));
      glUniform1f(location_alpha_, 1.0f);
      Vec<int> indices(vertices.size());
      std::iota(std::begin(indices), std::end(indices), 0);
      Vec<float> positions;
      Vec<float> colors;
      Vec<float> uvs;
      Vec<float> normals;
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

      auto index_buffer_id = m_rendererBase->GenNewBufId(nBufTypes::Indices, vao_id);
      auto position_buffer_id = m_rendererBase->GenNewBufId(nBufTypes::Positions3D, vao_id);
      auto color_buffer_id = m_rendererBase->GenNewBufId(nBufTypes::Colors, vao_id);
      auto uv_buffer_id = m_rendererBase->GenNewBufId(nBufTypes::Uvs, vao_id);
      auto normal_buffer_id = m_rendererBase->GenNewBufId(nBufTypes::Normals, vao_id);
      auto num_vertices = vertices.size();
      SetIndicesData(index_buffer_id, num_vertices, indices.data());
      SetData(
          position_buffer_id, num_vertices, positions.data(), nBufTypes::Positions3D,
          nRendModelsView::kLocationPosition);
      SetData(
          color_buffer_id, num_vertices, colors.data(), nBufTypes::Colors,
          nRendModelsView::kLocationColor);
      SetData(uv_buffer_id, num_vertices, uvs.data(), nBufTypes::Uvs, nRendModelsView::kLocationUv);
      SetData(
          normal_buffer_id, num_vertices, normals.data(), nBufTypes::Normals,
          nRendModelsView::kLocationNormal);
      UseVAOEnd();
   }
}
