#pragma once
#include "timeline.h"
#include <memory>
#include <string>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief A part of an animated 3D model.
   ////////////////////////////////////////////////////////////////////////////////
   class ModelPart
   {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Create internal data structures.
      ////////////////////////////////////////////////////////////////////////////////
      ModelPart()
          : timeline_(std::make_shared<Timeline>())
      {
      }

      auto texture_name()
      {
         return texture_name_;
      }

      void set_texture_name(std::string value)
      {
         texture_name_ = value;
      }

      auto timeline()
      {
         return timeline_;
      }

     private:
      std::string texture_name_;
      std::shared_ptr<Timeline> timeline_;
   };
}
