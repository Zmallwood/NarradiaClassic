#pragma once

namespace Narradia
{
   enum class BufferTypes
   {
      Indices,
      Positions2D,
      Positions3D,
      Colors,
      Uvs,
      Normals
   };

   class RendererBase
   {
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
}
