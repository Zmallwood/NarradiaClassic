#pragma once
#include "Object.h"
#include "world.actors/model/Mob.h"

namespace Narradia {
    class Tile {
      public:
        std::string_view ground() {
            return ground_;
        }

        void set_ground(std::string_view value) {
            ground_ = value;
        }

        std::shared_ptr<Object> object() {
            return object_;
        }

        void set_object(std::shared_ptr<Object> value) {
            object_ = value;
        }

        std::shared_ptr<Mob> mob() {
            return mob_;
        }

        void set_mob(std::shared_ptr<Mob> value) {
            mob_ = value;
        }

      private:
        std::string_view ground_;
        std::shared_ptr<Object> object_;
        std::shared_ptr<Mob> mob_;
    };
}
