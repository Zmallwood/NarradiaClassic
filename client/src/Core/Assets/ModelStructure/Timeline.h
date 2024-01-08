#pragma once

#include "Keyframe.h"

namespace Narradia {
   class Timeline {
     public:
      Map<float, SharedPtr<const Keyframe>> keyframes;
   };
}
