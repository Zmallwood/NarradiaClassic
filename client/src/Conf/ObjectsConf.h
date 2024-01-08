#pragma once
#include "ObjectConfEntry.h"

namespace Narradia {
   class ObjectsConf : public Singleton<ObjectsConf> {
     public:
      ObjectsConf();
      bool IsObstacle(StringView _objectType);
      float GetModelScaling(StringView _objectType);

     private:
      Map<StringView, ObjectConfEntry> m_objectConfs;
   };
}
