#pragma once
namespace Narradia
{
#if 1
   class MobConfEntry
   {
     public:
      int aggro_range = 0;
   };
#endif

   class MobsConf : public Singleton<MobsConf>
   {
     public:
      MobsConf();

      int GetAggroRange(std::string_view mob_type);

     private:
      std::map<std::string_view, MobConfEntry> mobs_confs_;
   };
}
