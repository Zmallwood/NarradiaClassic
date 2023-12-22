#pragma once
#include "renderer_base_view.h"
#include "../../matter/model/colors.h"
namespace Narradia
{
    class RendererTilesView : public RendererBaseView, public Singleton<RendererTilesView> {
      public:
        RendererTilesView();
        ~RendererTilesView();

        auto is_batch_drawing() {
            return is_batch_drawing_;
        }

        void set_is_batch_drawing(bool value) {
            is_batch_drawing_ = value;
        }

        auto location_projection() {
            return location_projection_;
        }

        auto location_view() {
            return location_view_;
        }

        auto location_model() {
            return location_model_;
        }

        auto location_alpha() {
            return location_alpha_;
        }

        auto location_view_pos() {
            return location_view_pos_;
        }

        auto location_fog_color() {
            return location_fog_color_;
        }

        static constexpr int kLocationPosition = 0;
        static constexpr int kLocationColor = 1;
        static constexpr int kLocationUv = 2;
        static constexpr int kLocationNormal = 3;
        inline static const Color kFogColorGround = Colors::purple;
      private:
        int location_projection_ = -1;
        int location_view_ = -1;
        int location_model_ = -1;
        int location_alpha_ = -1;
        int location_view_pos_ = -1;
        int location_fog_color_ = -1;
        bool is_batch_drawing_ = false;
    };
}
