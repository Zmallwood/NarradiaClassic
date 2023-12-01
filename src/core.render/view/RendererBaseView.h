#pragma once
#include "../model/RendererBase.h"
#include "ShaderProgramView.h"

namespace Narradia {
    class RendererBaseView {
      public:
        RendererBaseView();

      protected:
        void SetIndicesData(
            GLuint indices_vbo_id, int num_vertices, const void *data) const;

        void SetPositions2DData(
            GLuint pos_2d_vbo_id, int num_vertices, const void *data,
            int layout_location = -1) const;

        void SetPositions3DData(
            GLuint pos_3d_vbo_id, int num_vertices, const void *data,
            int layout_location = -1) const;

        void SetUvsData(
            GLuint uv_vbo_id, int num_vertices, const void *data,
            int layout_location = -1) const;

        void SetColorsData(
            GLuint color_vbo_id, int num_vertices, const void *data,
            int layout_location = -1) const;

        void SetNormalsData(
            GLuint normal_vbo_id, int num_vertices, const void *data,
            int layout_location = -1) const;

        void UpdateIndicesData(
            GLuint indices_vbo_id, std::vector<int> &indices) const;

        void UpdatePositions2DData(
            GLuint positions_vbo_id, std::vector<float> &positions,
            int layout_location) const;

        void UpdatePositions3DData(
            GLuint positions_vbo_id, std::vector<float> &positions,
            int layout_location) const;

        void UpdateUvsData(
            GLuint uvs_vbo_id, std::vector<float> &uvs,
            int layout_location) const;

        void UpdateColorsData(
            GLuint colors_vbo_id, std::vector<float> &colors,
            int layout_location) const;

        void UpdateNormalsData(
            GLuint normals_vbo_id, std::vector<float> &normals,
            int layout_location) const;

        void UseVaoBegin(int vao_id) const;

        void UseVaoEnd() const;

        GLuint GetUniformLocation(std::string_view var_name);

        std::shared_ptr<ShaderProgramView> GetShaderProgramView() const;

        void CleanupBase();

        std::shared_ptr<RendererBase> renderer_base_;

      private:
        void SetArrayBufferData(
            GLuint vbo_id, int num_vertices, const void *data,
            int num_floats_per_entry, int layout_location = -1) const;

        void UpdateArrayBufferData(
            GLuint vbo_id, std::vector<float> &data, int num_floats_per_entry,
            int layout_location) const;

        std::shared_ptr<ShaderProgramView> shader_program_view_;
    };
}
