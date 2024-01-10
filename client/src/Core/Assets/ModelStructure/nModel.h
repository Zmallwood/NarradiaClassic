#pragma once

#include "nModelPart.h"

namespace Narradia {
   class nModel {
     public:
      nModel(int _animDuration)
          : m_animDuration(_animDuration),
            m_modelParts(MakeShared<Vec<SharedPtr<nModelPart>>>()) {
      }

      auto GetAnimDuration() {
         return m_animDuration;
      }
      
      auto GetModelParts() {
         return m_modelParts;
      }

     private:
      const int m_animDuration;
      SharedPtr<Vec<SharedPtr<nModelPart>>> m_modelParts;
   };
}
