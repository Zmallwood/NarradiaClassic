#include "Configuration.h"

namespace Narradia {
   // ObjectsConf
   using ObjectFlags::NoObstacle;

   ObjectsConf::ObjectsConf() {
      m_objectConfs["ObjectPoolOfBlood"] = {NoObstacle, 1.0f};
      m_objectConfs["ObjectTree1"] = {0, 6.0f};
      m_objectConfs["ObjectTree2"] = {0, 6.0f};
      m_objectConfs["ObjectBush1"] = {0, 3.0f};
      m_objectConfs["ObjectStoneBoulder"] = {0, 3.0f};
   }
   bool ObjectsConf::IsObstacle(StringView _objectType) {
      return m_objectConfs.count(_objectType) == 0
                 ? true
                 : (m_objectConfs.at(_objectType).flags & NoObstacle) == 0;
   }
   float ObjectsConf::GetModelScaling(StringView _objectType) {
      return m_objectConfs.count(_objectType) == 0 ? 1.0f
                                                   : m_objectConfs.at(_objectType).modelScaling;
   }

   // MobsConf
   MobsConf::MobsConf() {
      m_mobsConfs["MobBoar"] = {4};
      m_mobsConfs["MobTroll"] = {6};
      m_mobsConfs["MobEvilSpirit"] = {8};
   }
   int MobsConf::GetAggroRange(StringView _mobType) {
      if (m_mobsConfs.count(_mobType) == 0)
         return 0;
      else
         return m_mobsConfs.at(_mobType).aggroRange;
   }
}
