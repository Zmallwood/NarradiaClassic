#include "nObjectsConf.h"
#include "ObjectFlags.h"

namespace Narradia {
   using ObjectFlags::NoObstacle;

   nObjectsConf::nObjectsConf() {
      m_objectConfs["ObjectPoolOfBlood"] = {NoObstacle, 1.0f};
      m_objectConfs["ObjectTree1"] = {0, 6.0f};
      m_objectConfs["ObjectTree2"] = {0, 6.0f};
      m_objectConfs["ObjectBush1"] = {0, 3.0f};
      m_objectConfs["ObjectStoneBoulder"] = {0, 3.0f};
   }

   bool nObjectsConf::IsObstacle(StringView _objectType) {
      return m_objectConfs.count(_objectType) == 0
                 ? true
                 : (m_objectConfs.at(_objectType).flags & NoObstacle) == 0;
   }

   float nObjectsConf::GetModelScaling(StringView _objectType) {
      return m_objectConfs.count(_objectType) == 0 ? 1.0f
                                                   : m_objectConfs.at(_objectType).modelScaling;
   }
}
