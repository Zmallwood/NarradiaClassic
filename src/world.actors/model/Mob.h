#pragma once

namespace Narradia {
    class Mob {
      public:
        Mob(std::string_view type)
            : type_(type) {
        }

        std::string_view type() {
            return type_;
        }

      private:
        std::string_view type_;
    };
}
