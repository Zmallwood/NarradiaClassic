#pragma once
#include "model_part_keyframe.h"

namespace Narradia {
  class ModelPartTimeline {
   public:
    std::map<float, std::shared_ptr<const ModelPartKeyframe>> keyframes;
  };
}
