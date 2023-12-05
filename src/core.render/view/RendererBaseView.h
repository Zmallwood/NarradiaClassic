#pragma once
#include "../model/RendererBase.h"
#include "ShaderProgramView.h"
#include "core.render/model/BufferTypes.h"

namespace Narradia {
    class RendererBaseView {
      public:
        RendererBaseView();

      protected:
        void SetIndicesData(
            GLuint indices_vbo_id, int num_vertices, const void *data) const;

        void SetData(
            GLuint vbo_id, int num_vertices, const void *data,
            BufferTypes buffer_type, int layout_location = -1) const;

        void UpdateIndicesData(
            GLuint indices_vbo_id, std::vector<int> &indices) const;

        void UpdateData(
            GLuint vbo_id, std::vector<float> &data, BufferTypes buffer_type,
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
