#pragma once

#include "RenderingCore.h"

namespace Narradia {
   class nRendGroundView: public nRendBaseView, public Singleton<nRendGroundView> {
     public:
      nRendGroundView();
      ~nRendGroundView();

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

      auto fog_color_ground() {
         return fog_color_ground_;
      }

      void set_fog_color_ground(Color value) {
         fog_color_ground_ = value;
      }

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
      static constexpr int kLocationUv = 2;
      static constexpr int kLocationNormal = 3;

     private:
      int location_projection_ = -1;
      int location_view_ = -1;
      int location_model_ = -1;
      int location_alpha_ = -1;
      int location_view_pos_ = -1;
      int location_fog_color_ = -1;
      Color fog_color_ground_;
      bool is_batch_drawing_ = false;
   };
}
