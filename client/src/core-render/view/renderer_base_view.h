#pragma once
#include "../model/buffer_types.h"
#include "../model/renderer_base.h"
#include "shader_program_view.h"
#include <GL/glew.h>
#include <memory>
#include <string_view>
#include <vector>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief View component of RendererBase.
   ////////////////////////////////////////////////////////////////////////////////
   class RendererBaseView {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Create shader program and renderer base.
      ////////////////////////////////////////////////////////////////////////////////
      RendererBaseView();

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Start using the renderers shader program and VAO with provided ID.
      ///
      /// @param[in] vao_id ID for VAO to use.
      ////////////////////////////////////////////////////////////////////////////////
      void UseVAOBegin(GLuint vao_id) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Stop using the currently used (any) VAO and the currently used (any) shader
      /// program.
      ////////////////////////////////////////////////////////////////////////////////
      void UseVAOEnd() const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Set indices data for rendered object.
      ///
      /// @param[in] indices_vbo_id VBO ID for index buffer.
      /// @param[in] num_vertices Number of vertices in provided input data.
      /// @param[in] data Indices data.
      ////////////////////////////////////////////////////////////////////////////////
      void SetIndicesData(GLuint indices_vbo_id, int num_vertices, const void *data) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Set all kinds of data, except indices, for rendered object.
      ///
      /// @param[in] vbo_id VBO ID for data buffer.
      /// @param[in] num_vertices Number of vertices in provided input data.
      /// @param[in] data Buffer data.
      /// @param[in] buffer_type Type of data.
      /// @param[in] layout_location Layout location in shader source.
      ////////////////////////////////////////////////////////////////////////////////
      void SetData(
          GLuint vbo_id, int num_vertices, const void *data, BufferTypes buffer_type,
          int layout_location = -1) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Update indices data for rendered object.
      ///
      /// @param[in] indices_vbo_id VBO ID for indices buffer.
      /// @param[in] indices Indices to move into the buffer.
      ////////////////////////////////////////////////////////////////////////////////
      void UpdateIndicesData(GLuint indices_vbo_id, std::vector<int> &indices) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Update all kinds of data, except for indices, for rendered object.
      ///
      /// @param[in] vbo_id VBO ID for buffer.
      /// @param[in] data Data to move into the buffer.
      /// @param[in] buffer_type Type of data.
      /// @param[in] layout_location Layout location in shader source.
      ////////////////////////////////////////////////////////////////////////////////
      void UpdateData(
          GLuint vbo_id, std::vector<float> &data, BufferTypes buffer_type,
          int layout_location) const;

      auto shader_program_view() {
         return shader_program_view_;
      }

      auto renderer_base() {
         return renderer_base_;
      }

     protected:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets the layout location in shader source for a uniform parameter with provided
      /// name.
      ///
      /// @param[in] var_name Parameter name.
      /// @return Layout location.
      ////////////////////////////////////////////////////////////////////////////////
      GLuint GetUniformLocation(std::string_view var_name);

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Forwards the cleanup command to the shader program view.
      ////////////////////////////////////////////////////////////////////////////////
      void CleanupBase();

      std::shared_ptr<RendererBase> renderer_base_;

     private:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Set data for a GL_ARRAY_BUFFER, that is all buffers except for indices.
      ///
      /// @param[in] vbo_id VBO ID for the buffer to move the data into.
      /// @param[in] num_vertices Number of vertices contained in the data.
      /// @param[in] data The data to move into the buffer.
      /// @param[in] num_floats_per_entry Number of floats per entry in the data.
      /// @param[in] layout_location Layout location in shader source.
      ////////////////////////////////////////////////////////////////////////////////
      void SetArrayBufferData(
          GLuint vbo_id, int num_vertices, const void *data, int num_floats_per_entry,
          int layout_location = -1) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Update data for a GL_ARRAY_BUFFER, that is all buffers except for indices.
      ///
      /// @param[in] vbo_id VBO ID for the buffer to move the data into.
      /// @param[in] data The data to move into the buffer.
      /// @param[in] num_floats_per_entry Number of floats per entry in the data.
      /// @param[in] layout_location Layout location in shader source.
      ////////////////////////////////////////////////////////////////////////////////
      void UpdateArrayBufferData(
          GLuint vbo_id, std::vector<float> &data, int num_floats_per_entry,
          int layout_location) const;

      std::shared_ptr<ShaderProgramView> shader_program_view_;
   };
}
