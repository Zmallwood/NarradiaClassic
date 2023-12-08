#pragma once
#include "RendererBaseView.h"

namespace Narradia {
    class RendererTilesView : public RendererBaseView, public Singleton<RendererTilesView> {
      public:
        RendererTilesView();
        ~RendererTilesView();
        void UpdateDrawTile(
            std::string_view image_name, RenderId vao_id, Vertex3F &v0, Vertex3F &v1, Vertex3F &v2,
            Vertex3F &v3, Point3F &normal00, Point3F &normal10, Point3F &normal11,
            Point3F &normal01, bool depth_test_off = false) const;
        void StartBatchDrawing();
        void StopBatchDrawing();

        bool is_batch_drawing() {
            return is_batch_drawing_;
        }

        int location_projection() {
            return location_projection_;
        }

        int location_view() {
            return location_view_;
        }

        int location_model() {
            return location_model_;
        }

        int location_alpha() {
            return location_alpha_;
        }

        int location_view_pos() {
            return location_view_pos_;
        }

        int location_fog_color() {
            return location_fog_color_;
        }

        static constexpr int kLocationPosition = 0;
        static constexpr int kLocationColor = 1;
        static constexpr int kLocationUv = 2;
        static constexpr int kLocationNormal = 3;
        inline static const Color kFogColorGround = Colors::mild_blue;

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
