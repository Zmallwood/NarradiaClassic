#pragma once

#include "nBufTypes.h"

namespace Narradia {
   class nRendBase;
   class ShaderProgramView;

   class nRendBaseView {
     public:
      nRendBaseView();
      void UseVAOBegin(GLuint _VAOID) const;
      void UseVAOEnd() const;
      void SetIndicesData(GLuint _indicesVBOID, int _numVertices, const void *_data) const;
      void SetData(
          GLuint _VBOID, int _numVertices, const void *_data, nBufTypes _bufType,
          int _layoutLocation = -1) const;
      void UpdateIndicesData(GLuint _indicesVBOID, Vec<int> &indices) const;
      void
      UpdateData(GLuint _VBOID, Vec<float> &_data, nBufTypes _bufType, int _layoutLocation) const;

      auto shader_program_view() {
         return shader_program_view_;
      }

      auto renderer_base() {
         return renderer_base_;
      }

     protected:
      GLuint GetUniformLocation(StringView _varName);
      void CleanupBase();

      SharedPtr<nRendBase> renderer_base_;

     private:
      void SetArrayBufferData(
          GLuint _VBOID, int _numVertices, const void *_data, int _numFloatsPerEntry,
          int _layoutLocation = -1) const;
      void UpdateArrayBufferData(
          GLuint _VBOID, Vec<float> &_data, int _numFloatsPerEntry, int _layoutLocation) const;

      SharedPtr<ShaderProgramView> shader_program_view_;
   };
}
