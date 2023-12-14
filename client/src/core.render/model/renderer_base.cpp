#include "renderer_base.h"
namespace Narradia
{
   auto RendererBase::GenNewVAOId() -> GLuint {
      GLuint new_vao_id;
      glGenVertexArrays(1, &new_vao_id);
      vao_ids_.push_back(new_vao_id);
      return new_vao_id;
   }

   auto RendererBase::GenNewBufId(BufferTypes buffer_type, GLuint vao_id) -> GLuint {
      GLuint new_buffer_id;
      glGenBuffers(1, &new_buffer_id);
      vbo_ids_[buffer_type][vao_id] = new_buffer_id;
      return new_buffer_id;
   }

   auto RendererBase::BufId(BufferTypes buffer_type, GLuint vao_id) const -> GLuint {
      return vbo_ids_.at(buffer_type).at(vao_id);
   }

   auto RendererBase::CleanupBase() const -> void {
      for (auto &buffer_type : vbo_ids_)
         for (auto &buffer_entry : buffer_type.second)
            glDeleteBuffers(1, &buffer_entry.second);
      for (auto vao_id : vao_ids_)
         glDeleteVertexArrays(1, &vao_id);
   }
}
