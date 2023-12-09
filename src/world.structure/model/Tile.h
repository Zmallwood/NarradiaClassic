#pragma once
#include "Object.h"
#include "TileEffect.h"
#include "world.actors/model/Mob.h"

namespace Narradia
{
    /**
     A tile in the game map on which objects can be places and actors can walk
     on.
    */
    class Tile {
      public:
        std::string_view ground() { return ground_; }
        void set_ground(std::string_view value) { ground_ = value; }

        std::shared_ptr<Object> object() { return object_; }
        void set_object(std::shared_ptr<Object> value) { object_ = value; }

        std::shared_ptr<Mob> mob() { return mob_; }
        void set_mob(std::shared_ptr<Mob> value) { mob_ = value; }

        float elevation() { return elevation_; }

        TileEffect tile_effect() { return tile_effect_; }
        void set_tile_effect(TileEffect value) { tile_effect_ = value; }

        RenderId rid() { return rid_; }
        void set_rid(RenderId value) { rid_ = value; }

      private:
        std::string_view ground_;
        std::shared_ptr<Object> object_;
        std::shared_ptr<Mob> mob_;
        float elevation_ = 0.0f;
        TileEffect tile_effect_;
        RenderId rid_;
    };
}
