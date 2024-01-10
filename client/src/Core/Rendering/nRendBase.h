#pragma once

#include "nBufTypes.h"

namespace Narradia {
   class nRendBase {
     public:
      GLuint GenNewVAOId();
      GLuint GenNewBufId(nBufTypes _bufType, GLuint _VAOID);
      GLuint BufId(nBufTypes _bufType, GLuint _VAOID) const;
      void CleanupBase() const;

      static constexpr int kNumVerticesInRectangle = 4;
      inline static const auto kNumFloatsPerEntry = Map<nBufTypes, int>{
          {nBufTypes::Indices, 1}, {nBufTypes::Positions2D, 2}, {nBufTypes::Positions3D, 3},
          {nBufTypes::Colors, 4},  {nBufTypes::Uvs, 2},         {nBufTypes::Normals, 3}};

     private:
      Vec<GLuint> m_VAOIDs;
      Map<nBufTypes, Map<GLuint, GLuint>> m_VBOIDs;
   };
}
