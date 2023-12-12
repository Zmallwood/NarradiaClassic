#pragma once
namespace Narradia
{
    class MapSaver : public Singleton<MapSaver> {
      public:
        void SaveWorldMapToFile();
      private:
        const std::string kMapName = "DefaultMap";
    };
}
