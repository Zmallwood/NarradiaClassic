#pragma once
#include "ObjectFlags.h"

namespace Narradia
{
    /**
    Sets custom object flags and returns custom properties for specific
    object types.
    */
    class ObjectsConfiguration : public Singleton<ObjectsConfiguration> {
      public:
        ObjectsConfiguration();
        bool BlocksSight(std::string_view object_type);
        bool IsObstacle(std::string_view object_type);

      private:
        std::map<std::string_view, int> object_flags_;
    };
}
