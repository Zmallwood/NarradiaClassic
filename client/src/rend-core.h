#pragma once

namespace Narradia
{
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
      auto perspective_matrix() {
         return perspective_matrix_;
      }
      void set_perspective_matrix(glm::mat4 value) {
         perspective_matrix_ = value;
      }
      auto view_matrix() {
         return view_matrix_;
      }
      void set_view_matrix(glm::mat4 value) {
         view_matrix_ = value;
      }

     private:
      glm::mat4 perspective_matrix_;
      glm::mat4 view_matrix_;
   };
#endif
}
