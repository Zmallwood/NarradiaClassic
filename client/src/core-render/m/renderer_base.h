#pragma once
#include "buffer_types.h"
#include <GL/glew.h>
#include <map>
#include <vector>
namespace Narradia
{
   class RendererBase
   {
     public:
      auto GenNewVAOId() -> GLuint;

      auto GenNewBufId(BufferTypes buffer_type, GLuint vao_id) -> GLuint;

      auto BufId(BufferTypes buffer_type, GLuint vao_id) const -> GLuint;

      static constexpr int kNumVerticesInRectangle = 4;
      inline static const auto kNumFloatsPerEntry = std::map<BufferTypes, int>{
          {BufferTypes::Indices, 1}, {BufferTypes::Positions2D, 2}, {BufferTypes::Positions3D, 3},
          {BufferTypes::Colors, 4},  {BufferTypes::Uvs, 2},         {BufferTypes::Normals, 3}};

      auto CleanupBase() const -> void;

     private:
      std::vector<GLuint> vao_ids_;
      std::map<BufferTypes, std::map<GLuint, GLuint>> vbo_ids_;
   };
}
