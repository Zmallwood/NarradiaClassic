#pragma once
#include "object_flags.h"
#include "object_conf_entry.h"

namespace Narradia {
  /**
   Sets custom object flags and returns custom properties
   for specific object types.
  */
  class ObjectsConf : public Singleton<ObjectsConf> {
   public:
    ObjectsConf();
    bool BlocksSight(std::string_view object_type);
    bool IsObstacle(std::string_view object_type);
    float GetModelScaling(std::string_view object_type);

   private:
    std::map<std::string_view, ObjectConfEntry> object_confs_;
  };
}
