#pragma once

#include "Timeline.h"

namespace Narradia {
   class ModelPart {
     public:
      ModelPart()
          : m_timeln(MakeShared<Timeline>()) {
      }

      auto TexName() {
         return m_texName;
      }

      void SetTexName(String value) {
         m_texName= value;
      }

      auto Timeln() {
         return m_timeln;
      }

     private:
      String m_texName;
      SharedPtr<Timeline> m_timeln;
   };
}
