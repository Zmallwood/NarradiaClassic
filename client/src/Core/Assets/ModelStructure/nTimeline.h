#pragma once

#include "nKeyframe.h"

namespace Narradia {
   class nTimeline {
     public:
      Map<float, SharedPtr<const nKeyframe>> keyframes;
   };
}
