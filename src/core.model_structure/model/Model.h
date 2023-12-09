#pragma once
#include "ModelPart.h"

namespace Narradia {
    class Model {
      public:
        Model(int anim_duration)
            : anim_duration_(anim_duration),
              model_parts_(std::make_shared<std::vector<std::shared_ptr<const ModelPart>>>()) {
        }

        auto model_parts() {
            return model_parts_;
        }

      private:
        const int anim_duration_;
        std::shared_ptr<std::vector<std::shared_ptr<const ModelPart>>> model_parts_;
    };
}
