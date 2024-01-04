#pragma once

namespace Narradia
{
   // Developer settings
#if 1
   constexpr bool kVerbose = false;
#endif
   // Constants for scaling of different aspect of the game world map
#if 1
   constexpr float kTileSize = 6.0f;
   constexpr float kElevAmount = 11.0f;
#endif

   // Show ObjectsConf sub components
#if 1
   namespace ObjectFlags
   {
      static constexpr int None = 0;
      static constexpr int NoObstacle = 1 << 0;
   }

   class ObjectConfEntry {
     public:
      int flags = 0;
      float model_scaling = 1.0f;
   };
#endif

   class ObjectsConf : public S<ObjectsConf> {
     public:
      ObjectsConf();
      bool IsObstacle(std::string_view object_type);
      float GetModelScaling(std::string_view object_type);

     private:
      std::map<std::string_view, ObjectConfEntry> object_confs_;
   };

   // Shoiw MobsConf sub components
#if 1
   class MobConfEntry {
     public:
      int aggro_range = 0;
   };
#endif

   class MobsConf : public S<MobsConf> {
     public:
      MobsConf();
      int GetAggroRange(std::string_view mob_type);

     private:
      std::map<std::string_view, MobConfEntry> mobs_confs_;
   };
}
