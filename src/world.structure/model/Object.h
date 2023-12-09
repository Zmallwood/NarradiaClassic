#pragma once

namespace Narradia
{
    /**
     * An object in the game world, such as on the map or in player inventory.
     */
    class Object {
      public:
        Object(std::string_view type);

        std::string_view type() { return type_; }
        void set_type(std::string_view value) { type_ = value; }

      private:
        std::string_view type_ = "";
    };
}
