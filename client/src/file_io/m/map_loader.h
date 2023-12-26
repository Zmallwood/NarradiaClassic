#pragma once
namespace Narradia
{
   class MapArea;
   class MapLoader : public Singleton<MapLoader>
   {
     public:
      void LoadWorldMapFromFile(std::shared_ptr<MapArea> &map_area, std::string map_name);
   };
}
