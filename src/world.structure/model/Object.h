#pragma once

namespace Narradia {
    class Object {
      public:
        Object(std::string_view type);

        std::string_view type() {
            return type_;
        }

        void set_type(std::string_view value) {
            type_ = value;
        }

      private:
        std::string_view type_ = "";
    };
}