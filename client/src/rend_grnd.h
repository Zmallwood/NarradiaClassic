#pragma once

#include "rend-core.h"

namespace Narradia
{
   // View
#if 1
   class RendGrndV : public RendBaseV, public S<RendGrndV> {
     public:
      RendGrndV();
      ~RendGrndV();

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
      inline static Color kFogColorGround = Colors::mild_blue;

     private:
      int location_projection_ = -1;
      int location_view_ = -1;
      int location_model_ = -1;
      int location_alpha_ = -1;
      int location_view_pos_ = -1;
      int location_fog_color_ = -1;
      bool is_batch_drawing_ = false;
   };

   // Free functions
#if 1
   RenderID NewTile();
   void SetTileGeom(RenderID vao_id, Square<Vertex3F> &verts);
   void DrawTile(std::string_view image_name, RenderID vao_id, bool depth_test_off = false);
   void StartTileBatchDrawing();
   void StopTileBatchDrawing();
#endif
#endif
}
