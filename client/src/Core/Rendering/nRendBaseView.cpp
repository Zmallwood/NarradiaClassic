#include "nRendBaseView.h"
#include "RenderingCore.h"
#include "nRendBase.h"

namespace Narradia {
   nRendBaseView::nRendBaseView()
       : m_shaderProgramView(MakeShared<nShaderProgramView>()),
         m_rendererBase(MakeShared<nRendBase>()) {
   }

   void
   nRendBaseView::SetIndicesData(GLuint _indicesVBOID, int _numVertices, const void *_data) const {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesVBOID);
      glBufferData(
          GL_ELEMENT_ARRAY_BUFFER,
          _numVertices * nRendBase::kNumFloatsPerEntry.at(nBufTypes::Indices) * sizeof(float),
          _data, GL_DYNAMIC_DRAW);
   }

   void nRendBaseView::SetData(
       GLuint _VBOID, int _numVertices, const void *_data, nBufTypes _bufType,
       int _layoutLocation) const {
      SetArrayBufferData(
          _VBOID, _numVertices, _data, nRendBase::kNumFloatsPerEntry.at(_bufType), _layoutLocation);
   }

   void nRendBaseView::SetArrayBufferData(
       GLuint _VBOID, int _numVertices, const void *_data, int _numFloatsPerEntry,
       int _layoutLocation) const {
      glBindBuffer(GL_ARRAY_BUFFER, _VBOID);
      glBufferData(
          GL_ARRAY_BUFFER, _numVertices * _numFloatsPerEntry * sizeof(float), _data,
          GL_DYNAMIC_DRAW);
      if (_layoutLocation >= 0) {
         glVertexAttribPointer(
             _layoutLocation, _numFloatsPerEntry, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)0);
         glEnableVertexAttribArray(_layoutLocation);
      }
   }

   void nRendBaseView::UpdateIndicesData(GLuint _indicesVBOID, Vec<int> &indices) const {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesVBOID);
      glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(float) * indices.size(), indices.data());
   }

   void nRendBaseView::UpdateArrayBufferData(
       GLuint _VBOID, Vec<float> &_data, int _numFloatsPerEntry, int _layoutLocation) const {
      glBindBuffer(GL_ARRAY_BUFFER, _VBOID);
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * _data.size(), _data.data());
      glVertexAttribPointer(
          _layoutLocation, _numFloatsPerEntry, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)0);
      glEnableVertexAttribArray(_layoutLocation);
   }

   void nRendBaseView::UpdateData(
       GLuint _VBOID, Vec<float> &_data, nBufTypes _bufType, int _layoutLocation) const {
      UpdateArrayBufferData(
          _VBOID, _data, nRendBase::kNumFloatsPerEntry.at(_bufType), _layoutLocation);
   }

   void nRendBaseView::UseVAOBegin(GLuint _VAOID) const {
      glUseProgram(m_shaderProgramView->shader_program()->program_id());
      glBindVertexArray(_VAOID);
   }

   void nRendBaseView::UseVAOEnd() const {
      glBindVertexArray(0);
      glUseProgram(0);
   }

   GLuint nRendBaseView::GetUniformLocation(StringView _varName) {
      return glGetUniformLocation(
          m_shaderProgramView->shader_program()->program_id(), _varName.data());
   }

   void nRendBaseView::CleanupBase() {
      m_shaderProgramView->shader_program()->Cleanup();
      m_rendererBase->CleanupBase();
   }
}
