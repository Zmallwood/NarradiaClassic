#pragma once

#include "Actors/Player.h"
#include "FileIO/WorldMapRdr.h"

namespace Narradia {

   // Show World sub classes

#if 1

   // Show MapArea sub classes
#if 1

   // Show Tile sub classes
#if 1

   class Object {
     public:
      Object(String type)
          : type_(type) {
      }

      auto type() {
         return type_;
      }

      void set_type(StringView value) {
         type_ = value;
      }

     private:
      String type_ = "";
   };

   class TileEffect {
     public:
      StringView type;
      int ticks_started = 0;
   };

#endif

   class Mob;

   class Tile {
     public:
      Tile()
          : color_(MakeShared<Color>()) {
      }

      void IncreaseElevation(float amount) {
         elevation_ += amount;
      }

      inline auto ground() {
         return ground_;
      }

      void set_ground(String value) {
         ground_ = value;
      }

      auto object() {
         return object_;
      }

      void set_object(SharedPtr<Object> value) {
         object_ = value;
      }

      auto mob() {
         return mob_;
      }

      void set_mob(SharedPtr<Mob> value) {
         mob_ = value;
      }

      auto elevation() {
         return elevation_;
      }

      void set_elevation(float value) {
         elevation_ = value;
      }

      auto tile_effect() {
         return tile_effect_;
      }

      void set_tile_effect(TileEffect value) {
         tile_effect_ = value;
      }

      auto rid() {
         return rid_;
      }

      void set_rid(RenderID value) {
         rid_ = value;
      }

      auto normal() {
         return normal_;
      }
      void set_normal(Point3F value) {
         normal_ = value;
      }

      auto color() {
         return color_;
      }

     private:
      String ground_;
      SharedPtr<Object> object_;
      SharedPtr<Mob> mob_;
      float elevation_ = 0.0f;
      TileEffect tile_effect_;
      RenderID rid_ = 0;
      Point3F normal_;
      SharedPtr<Color> color_;
   };

#endif

   class WorldArea {
     public:
      WorldArea(int width, int height)
          : mobs_mirror_(MakeShared<Map<SharedPtr<Mob>, Point>>()) {
         for (auto x = 0; x < width; x++) {
            tiles_.push_back(Vec<SharedPtr<Tile>>());

            for (auto y = 0; y < height; y++) {
               tiles_.at(x).push_back(MakeShared<Tile>());
            }
         }
      }

      inline SharedPtr<Tile> GetTile(int x, int y) {
         try {
            return tiles_.at(x).at(y);
         } catch (Exception &e) {
            throw std::runtime_error("Tried to access tile with an invalid coordinate.");
         }
      }

      inline SharedPtr<Tile> GetTile(Point coord) {
         return GetTile(coord.x, coord.y);
      }

      inline bool IsInsideMap(Point coord) {
         return coord.x < tiles_.size() && coord.y < tiles_.at(0).size();
      }

      inline int Width() {
         return tiles_.size();
      }

      inline int Height() {
         return tiles_.at(0).size();
      }

      void ClearAllRIDs() {
         for (auto y = 0; y < Height(); y++) {
            for (auto x = 0; x < Width(); x++) {
               tiles_.at(x).at(y)->set_rid(0);
            }
         }
      }

      auto mobs_mirror() {
         return mobs_mirror_;
      }

     private:
      Vec<Vec<SharedPtr<Tile>>> tiles_;
      SharedPtr<Map<SharedPtr<Mob>, Point>> mobs_mirror_;
   };

#endif

   class World : public Singleton<World> {
     public:
      World() {
         world_width_ = WorldMapRdr::get()->world_map_width();
         world_height_ = WorldMapRdr::get()->world_map_height();

         auto map_names = WorldMapRdr::get()->world_area_names();

         for (auto y = 0; y < world_height_; y++) {
            for (auto x = 0; x < world_width_; x++) {
               world_areas_[x][y] = nullptr;

               WorldMapRdr::get()->LoadWorldMapFromFile(world_areas_[x][y], map_names[x][y]);
            }
         }
      }

      inline SharedPtr<WorldArea> CurrWorldArea() {
         auto world_loc = Player::get()->world_location();

         return world_areas_[world_loc.x][world_loc.y];
      }

      SharedPtr<WorldArea> WorldAreaAt(Point location) {
         if (world_areas_.count(location.x) != 0)
            if (world_areas_.at(location.x).count(location.y) != 0)
               return world_areas_[location.x][location.y];

         return nullptr;
      }

      auto world_width() {
         return world_width_;
      }

      auto world_height() {
         return world_height_;
      }

      auto world_areas() {
         return world_areas_;
      }

     private:
      Map<int, Map<int, SharedPtr<WorldArea>>> world_areas_;
      int world_width_ = -1;
      int world_height_ = -2;
   };

}
