#pragma once

#include "nTimeline.h"

namespace Narradia {
   class nModelPart {
     public:
      nModelPart()
          : m_timeline(MakeShared<nTimeline>()) {
      }

      auto GetTexName() {
         return m_texName;
      }

      void SetTexName(String _value) {
         m_texName= _value;
      }

      auto GetTimeline() {
         return m_timeline;
      }

     private:
      String m_texName;
      SharedPtr<nTimeline> m_timeline;
   };
}
