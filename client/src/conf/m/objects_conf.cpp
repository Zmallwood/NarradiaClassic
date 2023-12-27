#include "objects_conf.h"

namespace Narradia
{
   using ObjectFlags::NoObstacle;

   ObjectsConf::ObjectsConf()
   {
      object_confs_["ObjectPoolOfBlood"] = {NoObstacle, 1.0f};
      object_confs_["ObjectTree1"] = {0, 3.0f};
      object_confs_["ObjectTree2"] = {0, 3.0f};
   }

   auto ObjectsConf::IsObstacle(std::string_view object_type) -> bool
   {
      return object_confs_.count(object_type) == 0
                 ? true
                 : (object_confs_.at(object_type).flags & NoObstacle) == 0;
   }

   auto ObjectsConf::GetModelScaling(std::string_view object_type) -> float
   {
      return object_confs_.count(object_type) == 0 ? 1.0f
                                                   : object_confs_.at(object_type).model_scaling;
   }
}
