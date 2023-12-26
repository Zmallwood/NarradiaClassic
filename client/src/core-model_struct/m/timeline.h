#pragma once
#include "keyframe.h"
namespace Narradia
{
   class Timeline
   {
     public:
      std::map<float, std::shared_ptr<const Keyframe>> keyframes;
   };
}
