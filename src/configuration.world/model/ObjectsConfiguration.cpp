#include "ObjectsConfiguration.h"
#include "configuration.world/model/ObjectFlags.h"

namespace Narradia {
    ObjectsConfiguration::ObjectsConfiguration() {
        object_flags_.insert(
            {"ObjectPoolOfBlood",
             ObjectFlags::NoObstacle | ObjectFlags::NoSightBlock});
    }

    bool ObjectsConfiguration::BlocksSight(std::string_view object_type) {
        if (object_flags_.count(object_type) == 0)
            return true;

        return (object_flags_.at(object_type) & ObjectFlags::NoSightBlock) == 0;
    }

    bool ObjectsConfiguration::IsObstacle(std::string_view object_type) {
        if (object_flags_.count(object_type) == 0)
            return true;

        return (object_flags_.at(object_type) & ObjectFlags::NoObstacle) == 0;
    }
}
