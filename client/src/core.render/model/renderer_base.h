#pragma once
#include "buffer_types.h"
#include <GL/glew.h>
#include <map>
#include <vector>
namespace Narradia
{
   class ShaderProgram;

   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Base class for all renderers providing functions for generating VAO and VBOs.
   ////////////////////////////////////////////////////////////////////////////////
   class RendererBase {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Generate ID for new vertex array object (VAO).
      ///
      /// @return ID for new the new VAO.
      ////////////////////////////////////////////////////////////////////////////////
      auto GenNewVAOId() -> GLuint;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Generate ID for new vertex buffer object (VBO).
      ///
      /// @param[in] buffer_type What type of content the buffer should hold.
      /// @param[in] vao_id ID for the VAO the buffer belongs to.
      /// @return ID for the new VBO.
      ////////////////////////////////////////////////////////////////////////////////
      auto GenNewBufId(BufferTypes buffer_type, GLuint vao_id) -> GLuint;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets VBO ID for an already created VAO and buffer type.
      ///
      /// @param[in] buffer_type The type of content the buffer holds.
      /// @param[in] vao_id ID for the VAO the buffer belongs to.
      /// @return ID for the VBO.
      ////////////////////////////////////////////////////////////////////////////////
      auto BufId(BufferTypes buffer_type, GLuint vao_id) const -> GLuint;

      static constexpr int kNumVerticesInRectangle = 4;
      inline static const auto kNumFloatsPerEntry = std::map<BufferTypes, int>{
          {BufferTypes::Indices, 1}, {BufferTypes::Positions2D, 2}, {BufferTypes::Positions3D, 3},
          {BufferTypes::Colors, 4},  {BufferTypes::Uvs, 2},         {BufferTypes::Normals, 3}};

     protected:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Cleanup VAO and VBOs at object disposal.
      ////////////////////////////////////////////////////////////////////////////////
      auto CleanupBase() const -> void;

     private:
      std::vector<GLuint> vao_ids_;
      std::map<BufferTypes, std::map<GLuint, GLuint>> vbo_ids_;
   };
}
