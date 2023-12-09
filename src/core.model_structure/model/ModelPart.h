#pragma once
#include "ModelPartTimeline.h"

namespace Narradia {
    class ModelPart {
      public:
        ModelPart()
            : timeline_(std::make_shared<ModelPartTimeline>()) {
        }

        auto texture_name() {
            return texture_name_;
        }

        void set_texture_name(std::string value) {
            texture_name_ = value;
        }

        auto timeline() {
            return timeline_;
        }

      private:
        std::string texture_name_;
        std::shared_ptr<ModelPartTimeline> timeline_;
    };
}
