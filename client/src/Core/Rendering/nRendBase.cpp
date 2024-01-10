#include "nRendBase.h"

namespace Narradia {
   GLuint nRendBase::GenNewVAOId() {
      GLuint _newVAOID;
      glGenVertexArrays(1, &_newVAOID);
      m_VAOIDs.push_back(_newVAOID);
      return _newVAOID;
   }

   GLuint nRendBase::GenNewBufId(nBufTypes _bufType, GLuint _VAOID) {
      GLuint _newBufID;
      glGenBuffers(1, &_newBufID);
      m_VBOIDs[_bufType][_VAOID] = _newBufID;
      return _newBufID;
   }

   GLuint nRendBase::BufId(nBufTypes _bufType, GLuint _VAOID) const {
      return m_VBOIDs.at(_bufType).at(_VAOID);
   }

   void nRendBase::CleanupBase() const {
      for (auto &_bufType : m_VBOIDs)
         for (auto &_bufferEntry : _bufType.second)
            glDeleteBuffers(1, &_bufferEntry.second);
      for (auto _VAOID : m_VAOIDs)
         glDeleteVertexArrays(1, &_VAOID);
   }
}
