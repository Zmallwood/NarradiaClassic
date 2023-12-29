#pragma once

namespace Narradia
{
   class WorldArea;

   class WorldMapLoader: public S<WorldMapLoader>
   {
     public:
      WorldMapLoader();
      void LoadWorldMapFromFile(std::shared_ptr<WorldArea> &world_area, std::string map_name);
      auto world_map_width()
      {
         return world_map_width_;
      }
      auto world_map_height()
      {
         return world_map_height_;
      }
      auto world_area_names()
      {
         return world_area_names_;
      }

     private:
      int world_map_width_ = -1;
      int world_map_height_ = -1;
      std::map<int, std::map<int, std::string>> world_area_names_;

      const std::string kFileName = "World.conf";
   };
}
