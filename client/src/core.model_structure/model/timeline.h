#pragma once
#include "keyframe.h"
#include <map>
#include <memory>
namespace Narradia
{
    class Timeline {
      public:
        std::map<float, std::shared_ptr<const Keyframe>> keyframes;
    };
}
