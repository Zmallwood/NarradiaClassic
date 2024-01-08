#pragma once

namespace Narradia {

    // Developer settings

#if 1
    constexpr bool kVerbose = false;
#endif

    // Constants for scaling of different aspect of the game world map

#if 1
    constexpr float kTileSize = 6.0f;
    constexpr float kElevAmount = 11.0f;
    const Color kClearColor = Colors::mild_blue;
    const Color kFogColorGround = Colors::mild_blue;
    const Color kFogColorModels = Colors::mild_blue;
#endif

    // Show ObjectsConf sub components

#if 1
    namespace Object_Flags {

        static constexpr int None = 0;
        static constexpr int NoObstacle = 1 << 0;
    }

    class Object_Conf_Entry {
      public:
        int flags = 0;
        float model_scaling = 1.0f;
    };
#endif

    class Objects_Conf : public Singleton<Objects_Conf> {

      public:
        Objects_Conf();
        bool IsObstacle(String_View object_type);
        float GetModelScaling(String_View object_type);

      private:
        Map<String_View, Object_Conf_Entry> object_confs_;
    };

    // Shoiw MobsConf sub components

#if 1
    class Mob_Conf_Entry {

      public:
        int aggro_range = 0;
    };
#endif

    class Mobs_Conf : public Singleton<Mobs_Conf> {

      public:
        Mobs_Conf();
        int GetAggroRange(String_View mob_type);

      private:
        Map<String_View, Mob_Conf_Entry> mobs_confs_;
    };

}
