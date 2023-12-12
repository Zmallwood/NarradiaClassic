#include "objects_conf.h"
namespace Narradia
{
    using ObjectFlags::NoObstacle;
    using ObjectFlags::NoSightBlock;

    /**
     * @brief Sets custom object flags on startup.
     *
     */
    ObjectsConf::ObjectsConf() {
        object_confs_.insert({"ObjectPoolOfBlood", {NoObstacle | NoSightBlock, 1.0f}});
        object_confs_.insert({"ObjectTree1", {0, 6.0f}});
        object_confs_.insert({"ObjectTree2", {0, 6.0f}});
    }

    bool ObjectsConf::BlocksSight(std::string_view object_type) {
        if (object_confs_.count(object_type) == 0)
            return true;
        return (object_confs_.at(object_type).flags & NoSightBlock) == 0;
    }

    bool ObjectsConf::IsObstacle(std::string_view object_type) {
        if (object_confs_.count(object_type) == 0)
            return true;
        return (object_confs_.at(object_type).flags & NoObstacle) == 0;
    }

    float ObjectsConf::GetModelScaling(std::string_view object_type) {
        if (object_confs_.count(object_type) == 0)
            return 1.0f;
        return object_confs_.at(object_type).model_scaling;
    }
}
