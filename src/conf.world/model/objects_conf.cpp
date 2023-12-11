#include "objects_conf.h"
namespace Narradia {
  /**
   Set custom object flags on startup.
  */
  ObjectsConf::ObjectsConf() {
    object_confs_.insert(
        {"ObjectPoolOfBlood", {ObjectFlags::NoObstacle | ObjectFlags::NoSightBlock, 1.0f}});
    object_confs_.insert({"ObjectTree1", {0, 2.0f}});
    object_confs_.insert({"ObjectTree2", {0, 2.0f}});
  }

  bool ObjectsConf::BlocksSight(std::string_view object_type) {
    if (object_confs_.count(object_type) == 0)
      return true;
    return (object_confs_.at(object_type).flags & ObjectFlags::NoSightBlock) == 0;
  }

  /**
   Tells if an object is being flagged as an obstacle,
   returns to true if no flag is set.
  */
  bool ObjectsConf::IsObstacle(std::string_view object_type) {
    if (object_confs_.count(object_type) == 0)
      return true;
    return (object_confs_.at(object_type).flags & ObjectFlags::NoObstacle) == 0;
  }

  float ObjectsConf::GetModelScaling(std::string_view object_type) {
    if (object_confs_.count(object_type) == 0)
      return 1.0f;
    return object_confs_.at(object_type).model_scaling;
  }
}
