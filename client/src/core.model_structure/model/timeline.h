#pragma once
#include "keyframe.h"
#include <map>
#include <memory>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief A timeline belonging to a ModelPart, containing keyframes in an animation.
   ////////////////////////////////////////////////////////////////////////////////
   class Timeline {
     public:
      std::map<float, std::shared_ptr<const Keyframe>> keyframes;
   };
}
