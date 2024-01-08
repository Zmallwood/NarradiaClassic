#pragma once

namespace Narradia {
   // Show ObjectsConf sub components
   namespace ObjectFlags {
      static constexpr int None = 0;
      static constexpr int NoObstacle = 1 << 0;
   }

   class ObjectConfEntry {
     public:
      int flags = 0;
      float modelScaling = 1.0f;
   };

   class ObjectsConf : public Singleton<ObjectsConf> {
     public:
      ObjectsConf();
      bool IsObstacle(StringView _objectType);
      float GetModelScaling(StringView _objectType);

     private:
      Map<StringView, ObjectConfEntry> m_objectConfs;
   };

   // Shoiw MobsConf sub components
   class MobConfEntry {
     public:
      int aggroRange = 0;
   };

   class MobsConf : public Singleton<MobsConf> {
     public:
      MobsConf();
      int GetAggroRange(StringView _mobType);

     private:
      Map<StringView, MobConfEntry> m_mobsConfs;
   };

}
