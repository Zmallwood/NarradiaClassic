#pragma once

#include "Timeline.h"

namespace Narradia {
   class ModelPart {
     public:
      ModelPart()
          : m_timeln(MakeShared<Timeline>()) {
      }

      auto GetTexName() {
         return m_texName;
      }
      void SetTexName(String _value) {
         m_texName= _value;
      }
      auto GetTimeln() {
         return m_timeln;
      }

     private:
      String m_texName;
      SharedPtr<Timeline> m_timeln;
   };
}
