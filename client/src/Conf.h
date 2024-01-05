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
   const Color kClearColor = Colors::sky_blue;
   const Color kFogColorGround = Colors::sky_blue;
   const Color kFogColorModels = Colors::sky_blue;
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
      bool IsObstacle(StringView object_type);
      float GetModelScaling(StringView object_type);

     private:
      Map<StringView, ObjectConfEntry> object_confs_;
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
      int GetAggroRange(StringView mob_type);

     private:
      Map<StringView, MobConfEntry> mobs_confs_;
   };

}
