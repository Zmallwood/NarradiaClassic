#pragma once
#include <GL/glew.h>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Simple holding class for a GL program, of which every renderer has one.
   ////////////////////////////////////////////////////////////////////////////////
   class ShaderProgram
   {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Delete shader program when no longer used.
      ////////////////////////////////////////////////////////////////////////////////
      void Cleanup();

      auto program_id() const
      {
         return program_id_;
      }

      void set_program_id(GLuint value)
      {
         program_id_ = value;
      }

     private:
      GLuint program_id_ = 0;
   };
}
