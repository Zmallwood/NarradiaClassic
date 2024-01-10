#pragma once

#include "nBufTypes.h"

namespace Narradia {
   class nRendBase;
   class nShaderProgramView;

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

      auto ShaderProgramView() {
         return m_shaderProgramView;
      }
      auto RendererBase() {
         return m_rendererBase;
      }

     protected:
      GLuint GetUniformLocation(StringView _varName);
      void CleanupBase();

      SharedPtr<nRendBase> m_rendererBase;

     private:
      void SetArrayBufferData(
          GLuint _VBOID, int _numVertices, const void *_data, int _numFloatsPerEntry,
          int _layoutLocation = -1) const;
      void UpdateArrayBufferData(
          GLuint _VBOID, Vec<float> &_data, int _numFloatsPerEntry, int _layoutLocation) const;

      SharedPtr<nShaderProgramView> m_shaderProgramView;
   };
}
