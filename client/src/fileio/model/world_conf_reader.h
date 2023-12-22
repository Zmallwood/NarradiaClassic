#pragma once
namespace Narradia
{
   class WorldConfReader : public Singleton<WorldConfReader> {
     public:
      WorldConfReader();

      auto world_map_width() {
         return world_map_width_;
      }
      auto world_map_height() {
         return world_map_height_;
      }
      auto map_area_names() {
         return map_area_names_;
      }

     private:
      int world_map_width_ = -1;
      int world_map_height_ = -1;
      std::map<int, std::map<int, std::string>> map_area_names_;

      const std::string kFileName = "World.conf";
   };
}
