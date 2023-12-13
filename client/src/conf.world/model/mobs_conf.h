#pragma once
#include "mob_conf_entry.h"
namespace Narradia
{
   class MobsConf : public Singleton<MobsConf> {
     public:
      MobsConf();

      int GetAggroRange(std::string_view mob_type);

     private:
      std::map<std::string_view, MobConfEntry> mobs_confs_;
   };
}
