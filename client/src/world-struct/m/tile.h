#pragma once

namespace Narradia
{
   // Show sub classes
#if 1
   class TileEffect
   {
     public:
      std::string_view type;
      int ticks_started = 0;
   };
#endif

   class Object;
   class Mob;

   class Tile
   {
     public:
      Tile()
          : color_(std::make_shared<Color>())
      {
      }
      void IncreaseElevation(float amount);

      auto ground()
      {
         return ground_;
      }

      void set_ground(std::string value)
      {
         ground_ = value;
      }

      auto object()
      {
         return object_;
      }

      void set_object(std::shared_ptr<Object> value)
      {
         object_ = value;
      }

      auto mob()
      {
         return mob_;
      }

      void set_mob(std::shared_ptr<Mob> value)
      {
         mob_ = value;
      }

      auto elevation()
      {
         return elevation_;
      }

      void set_elevation(float value)
      {
         elevation_ = value;
      }

      auto tile_effect()
      {
         return tile_effect_;
      }

      void set_tile_effect(TileEffect value)
      {
         tile_effect_ = value;
      }

      auto rid()
      {
         return rid_;
      }

      void set_rid(RenderID value)
      {
         rid_ = value;
      }

      auto normal()
      {
         return normal_;
      }

      void set_normal(Point3F value)
      {
         normal_ = value;
      }

      auto color()
      {
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
}
