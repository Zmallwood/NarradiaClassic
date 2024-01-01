#pragma once

namespace Narradia
{
   // Model
   enum class BufferTypes { Indices, Positions2D, Positions3D, Colors, Uvs, Normals };

   class RendBase {
     public:
      GLuint GenNewVAOId();
      GLuint GenNewBufId(BufferTypes buffer_type, GLuint vao_id);
      GLuint BufId(BufferTypes buffer_type, GLuint vao_id) const;
      void CleanupBase() const;

      static constexpr int kNumVerticesInRectangle = 4;
      inline static const auto kNumFloatsPerEntry = std::map<BufferTypes, int>{
          {BufferTypes::Indices, 1}, {BufferTypes::Positions2D, 2}, {BufferTypes::Positions3D, 3},
          {BufferTypes::Colors, 4},  {BufferTypes::Uvs, 2},         {BufferTypes::Normals, 3}};

     private:
      std::vector<GLuint> vao_ids_;
      std::map<BufferTypes, std::map<GLuint, GLuint>> vbo_ids_;
   };

   // Belonging ShaderProgram class
#if 1
   class ShaderProgram {
     public:
      void Cleanup();
      auto program_id() const {
         return program_id_;
      }
      void set_program_id(GLuint value) {
         program_id_ = value;
      }

     private:
      GLuint program_id_ = 0;
   };
#endif

// CameraGL using for tiles- and models rendering.
#if 1
   class CameraGL : public S<CameraGL> {
     public:
      auto persp_matrix() {
         return persp_matrix_;
      }
      void set_persp_matrix(glm::mat4 value) {
         persp_matrix_ = value;
      }
      auto view_matrix() {
         return view_matrix_;
      }
      void set_view_matrix(glm::mat4 value) {
         view_matrix_ = value;
      }

     private:
      glm::mat4 persp_matrix_;
      glm::mat4 view_matrix_;
   };
#endif
// View
#if 1
   class RendBase;
   class ShaderProgramV;

   class RendBaseV {
     public:
      RendBaseV();
      void UseVAOBegin(GLuint vao_id) const;
      void UseVAOEnd() const;
      void SetIndicesData(GLuint indices_vbo_id, int num_vertices, const void *data) const;
      void SetData(
          GLuint vbo_id, int num_vertices, const void *data, BufferTypes buffer_type,
          int layout_location = -1) const;
      void UpdateIndicesData(GLuint indices_vbo_id, std::vector<int> &indices) const;
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
      GLuint GetUniformLocation(std::string_view var_name);
      void CleanupBase();

      std::shared_ptr<RendBase> renderer_base_;

     private:
      void SetArrayBufferData(
          GLuint vbo_id, int num_vertices, const void *data, int num_floats_per_entry,
          int layout_location = -1) const;
      void UpdateArrayBufferData(
          GLuint vbo_id, std::vector<float> &data, int num_floats_per_entry,
          int layout_location) const;

      std::shared_ptr<ShaderProgramV> shader_program_view_;
   };

   // Belonging ShaderProgramV class
#if 1
   class ShaderProgram;

   class ShaderProgramV {
     public:
      ShaderProgramV();
      bool Create(const GLchar *vert_shader_src, const GLchar *frag_shader_src);
      auto shader_program() {
         return shader_program_;
      }

     private:
      auto CompileShader(const GLchar *shader_src, GLuint *shader, GLenum shader_type) -> GLuint;

      std::shared_ptr<ShaderProgram> shader_program_;
   };
#endif
#endif
}
