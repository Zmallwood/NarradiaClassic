#include "mobs_conf.h"
namespace Narradia
{
   MobsConf::MobsConf()
   {
      mobs_confs_["MobBoar"] = {4};
      mobs_confs_["MobTroll"] = {6};
      mobs_confs_["MobEvilSpirit"] = {8};
   }

   int MobsConf::GetAggroRange(std::string_view mob_type)
   {
      if (mobs_confs_.count(mob_type) == 0)
         return 0;
      else
         return mobs_confs_.at(mob_type).aggro_range;
   }
}
