#pragma once

#include "nRendBaseView.h"
#include "nBodyData.h"

namespace Narradia {
   class nRendModelsView : public nRendBaseView, public Singleton<nRendModelsView> {
     public:
      nRendModelsView();
      ~nRendModelsView();
      RenderID NewBodyKeyframe(StringView model_name, float ms_time);
      void NewBodyKeyframeGeometry(
          GLuint vao_id, Vec<Vertex3F> vertices, Vec<Point3F> vertex_normals);

      auto timelines() {
         return timelines_;
      }

      auto model_ids() {
         return model_ids_;
      }

      auto location_projection() {
         return location_projection_;
      }

      auto location_view() {
         return location_view_;
      }

      auto location_alpha() {
         return location_alpha_;
      }

      auto location_model() {
         return location_model_;
      }

      auto location_model_no_translation() {
         return location_model_no_translation_;
      }

      auto location_color_mod() {
         return location_color_mod_;
      }

      auto location_view_pos() {
         return location_view_pos_;
      }

      auto location_fog_color() {
         return location_fog_color_;
      }

      auto location_no_fog() {
         return location_no_fog_;
      }

      auto location_no_lighting() {
         return location_no_lighting_;
      }

      auto global_animation_speed() {
         return global_animation_speed_;
      }

      auto is_batch_drawing() {
         return is_batch_drawing_;
      }

      void set_is_batch_drawing(bool value) {
         is_batch_drawing_ = value;
      }

      auto fog_color_models() {
         return fog_color_models_;
      }

      void set_fog_color_models(Color value) {
         fog_color_models_ = value;
      }

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
      static constexpr int kLocationUv = 2;
      static constexpr int kLocationNormal = 3;

     private:
      int location_projection_ = -1;
      int location_view_ = -1;
      int location_alpha_ = -1;
      int location_model_ = -1;
      int location_model_no_translation_ = -1;
      int location_color_mod_ = -1;
      int location_view_pos_ = -1;
      int location_fog_color_ = -1;
      int location_no_fog_ = -1;
      int location_no_lighting_ = -1;
      SharedPtr<Map<String, Map<int, Map<float, const nBodyData>>>> model_ids_;
      SharedPtr<Map<StringView, Map<float, RenderID>>> timelines_;
      float global_animation_speed_ = 1.0f;
      Color fog_color_models_;
      bool is_batch_drawing_ = false;
   };
}
