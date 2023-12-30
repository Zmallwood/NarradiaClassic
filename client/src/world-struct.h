#pragma once

namespace Narradia
{
   // Show World sub classes
#if 1

   // Show MapArea sub classes
#if 1

   // Show Tile sub classes
#if 1

   class Object {
     public:
      Object(std::string type);
      auto type() {
         return type_;
      }
      void set_type(std::string_view value) {
         type_ = value;
      }

     private:
      std::string type_ = "";
   };

   class TileEffect {
     public:
      std::string_view type;
      int ticks_started = 0;
   };

#endif

   class Mob;

   class Tile {
     public:
      Tile()
          : color_(std::make_shared<Color>()) {
      }
      void IncreaseElevation(float amount);
      auto ground() {
         return ground_;
      }
      void set_ground(std::string value) {
         ground_ = value;
      }
      auto object() {
         return object_;
      }
      void set_object(std::shared_ptr<Object> value) {
         object_ = value;
      }
      auto mob() {
         return mob_;
      }
      void set_mob(std::shared_ptr<Mob> value) {
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
      std::string ground_;
      std::shared_ptr<Object> object_;
      std::shared_ptr<Mob> mob_;
      float elevation_ = 0.0f;
      TileEffect tile_effect_;
      RenderID rid_ = 0;
      Point3F normal_;
      std::shared_ptr<Color> color_;
   };

#endif

   class WorldArea {
     public:
      WorldArea(int width, int height);
      std::shared_ptr<Tile> GetTile(int x, int y);
      std::shared_ptr<Tile> GetTile(Point coord);
      bool IsInsideMap(Point coord);
      int GetWidth();
      int GetHeight();
      void ClearAllRIDS();
      auto mobs_mirror() {
         return mobs_mirror_;
      }

     private:
      std::vector<std::vector<std::shared_ptr<Tile>>> tiles_;
      std::shared_ptr<std::map<std::shared_ptr<Mob>, Point>> mobs_mirror_;
   };

#endif

   class World : public S<World> {
     public:
      World();
      auto CurrWorldArea() -> std::shared_ptr<WorldArea>;
      auto WorldAreaAt(Point location) -> std::shared_ptr<WorldArea>;
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
      std::map<int, std::map<int, std::shared_ptr<WorldArea>>> world_areas_;
      int world_width_ = -1;
      int world_height_ = -1;
   };
}
