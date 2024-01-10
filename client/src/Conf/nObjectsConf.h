#pragma once
#include "nObjectConfEntry.h"

namespace Narradia {
   class nObjectsConf : public Singleton<nObjectsConf> {
     public:
      nObjectsConf();
      bool IsObstacle(StringView _objectType);
      float GetModelScaling(StringView _objectType);

     private:
      Map<StringView, nObjectConfEntry> m_objectConfs;
   };
}
