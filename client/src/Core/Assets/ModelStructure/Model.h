#pragma once

#include "ModelPart.h"

namespace Narradia {
   class Model {
     public:
      Model(int _animDuration)
          : m_animDuration(_animDuration),
            m_modelParts(MakeShared<Vec<SharedPtr<ModelPart>>>()) {
      }

      auto GetAnimDuration() {
         return m_animDuration;
      }
      auto GetModelParts() {
         return m_modelParts;
      }

     private:
      const int m_animDuration;
      SharedPtr<Vec<SharedPtr<ModelPart>>> m_modelParts;
   };
}
