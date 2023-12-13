#pragma once
#include "object_conf_entry.h"
#include "object_flags.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Sets custom object flags and returns custom properties for specific object types.
   ////////////////////////////////////////////////////////////////////////////////
   class ObjectsConf : public Singleton<ObjectsConf> {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Sets custom object flags on startup.
      ////////////////////////////////////////////////////////////////////////////////
      ObjectsConf();

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Tells if object of type is an obstacle for movement.
      ///
      /// @param[in] object_type Object type for which to check.
      /// @return True if its an obstacle or else false.
      ////////////////////////////////////////////////////////////////////////////////
      auto IsObstacle(std::string_view object_type) -> bool;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets scaling factor for 3D model used to render specified object.
      ///
      /// @param[in] object_type Object type to get scaling factor for.
      /// @return Scaling factor as a scaling multiple.
      ////////////////////////////////////////////////////////////////////////////////
      auto GetModelScaling(std::string_view object_type) -> float;

     private:
      std::map<std::string_view, ObjectConfEntry> object_confs_;
   };
}
