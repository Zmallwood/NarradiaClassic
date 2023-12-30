#include "conf.h"

namespace Narradia
{
   // ObjectsConf
#if 1
   using ObjectFlags::NoObstacle;
   ObjectsConf::ObjectsConf() {
      object_confs_["ObjectPoolOfBlood"] = {NoObstacle, 1.0f};
      object_confs_["ObjectTree1"] = {0, 6.0f};
      object_confs_["ObjectTree2"] = {0, 6.0f};
      object_confs_["ObjectBush1"] = {0, 3.0f};
      object_confs_["ObjectStoneBoulder"] = {0, 3.0f};
   }
   auto ObjectsConf::IsObstacle(std::string_view object_type) -> bool {
      return object_confs_.count(object_type) == 0
                 ? true
                 : (object_confs_.at(object_type).flags & NoObstacle) == 0;
   }
   auto ObjectsConf::GetModelScaling(std::string_view object_type) -> float {
      return object_confs_.count(object_type) == 0 ? 1.0f
                                                   : object_confs_.at(object_type).model_scaling;
   }
#endif

   // MobsConf
#if 1
   MobsConf::MobsConf() {
      mobs_confs_["MobBoar"] = {4};
      mobs_confs_["MobTroll"] = {6};
      mobs_confs_["MobEvilSpirit"] = {8};
   }
   int MobsConf::GetAggroRange(std::string_view mob_type) {
      if (mobs_confs_.count(mob_type) == 0)
         return 0;
      else
         return mobs_confs_.at(mob_type).aggro_range;
   }
#endif
}
