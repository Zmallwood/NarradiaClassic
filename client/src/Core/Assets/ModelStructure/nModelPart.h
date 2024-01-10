#pragma once

#include "nTimeline.h"

namespace Narradia {
   class nModelPart {
     public:
      nModelPart()
          : m_timeline(MakeShared<nTimeline>()) {
      }

      auto TexName() {
         return m_texName;
      }

      void SetTexName(String _value) {
         m_texName= _value;
      }

      auto Timeline() {
         return m_timeline;
      }

     private:
      String m_texName;
      SharedPtr<nTimeline> m_timeline;
   };
}
