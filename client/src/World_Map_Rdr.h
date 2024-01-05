#pragma once

namespace Narradia
{

   class WorldArea;

   class WorldMapRdr : public S<WorldMapRdr> {
     public:
      WorldMapRdr();
      void LoadWorldMapFromFile(SharedPtr<WorldArea> &world_area, String map_name);

      auto world_map_width() {
         return world_map_width_;
      }

      auto world_map_height() {
         return world_map_height_;
      }

      auto world_area_names() {
         return world_area_names_;
      }

     private:
      int world_map_width_ = -1;
      int world_map_height_ = -1;
      Map<int, Map<int, String>> world_area_names_;

      const String kFileName = "World.conf";
   };

}
