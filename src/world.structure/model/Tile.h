#pragma once
#include "Object.h"

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

      private:
        std::string_view ground_;
        std::shared_ptr<Object> object_;
    };
}