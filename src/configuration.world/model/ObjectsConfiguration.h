#pragma once
#include "ObjectFlags.h"

namespace Narradia {
    class ObjectsConfiguration : public Singleton<ObjectsConfiguration> {
      public:
        ObjectsConfiguration();

        bool BlocksSight(std::string_view object_type);

        bool IsObstacle(std::string_view object_type);

      private:
        std::map<std::string_view, int> object_flags_;
    };
}
