#pragma once
#include "ModelPartTimeline.h"

namespace Narradia {
    class ModelPart {
      public:
        ModelPart()
            : timeline_(std::make_shared<ModelPartTimeline>()) {
        }

        void set_texture_name(std::string_view value) {
            texture_name_ = value;
        }

        auto timeline() {
            return timeline_;
        }

      private:
        std::string_view texture_name_;
        std::shared_ptr<ModelPartTimeline> timeline_;
    };
}
