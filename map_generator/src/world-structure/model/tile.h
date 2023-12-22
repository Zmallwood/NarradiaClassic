#pragma once
#include "object.h"
#include "world-actors/model/mob.h"
namespace Narradia
{
    /**
     A tile in the game map on which objects can be places and
     actors can walk on.
    */
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

        auto color() {
            return color_;
        }

        auto normal() {
            return normal_;
        }

        void set_normal(Point3F value) {
            normal_ = value;
        }
      private:
        std::string ground_;
        std::shared_ptr<Object> object_;
        std::shared_ptr<Mob> mob_;
        float elevation_ = 0.0f;
        std::shared_ptr<Color> color_;
        Point3F normal_;
    };
}
