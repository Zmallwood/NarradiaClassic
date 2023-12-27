#pragma once

#include "render/body_data.h"
#include "render/renderer_base_v.h"

namespace Narradia
{
   class RendererModelsV : public RendererBaseV, public S<RendererModelsV>
   {
     public:
      RendererModelsV();
      ~RendererModelsV();
      auto timelines()
      {
         return timelines_;
      }
      auto model_ids()
      {
         return model_ids_;
      }
      auto location_projection()
      {
         return location_projection_;
      }
      auto location_view()
      {
         return location_view_;
      }
      auto location_alpha()
      {
         return location_alpha_;
      }
      auto location_model()
      {
         return location_model_;
      }
      auto location_model_no_translation()
      {
         return location_model_no_translation_;
      }
      auto location_color_mod()
      {
         return location_color_mod_;
      }
      auto location_view_pos()
      {
         return location_view_pos_;
      }
      auto location_fog_color()
      {
         return location_fog_color_;
      }
      auto location_no_fog()
      {
         return location_no_fog_;
      }
      auto location_no_lighting()
      {
         return location_no_lighting_;
      }
      auto global_animation_speed()
      {
         return global_animation_speed_;
      }
      auto is_batch_drawing()
      {
         return is_batch_drawing_;
      }
      void set_is_batch_drawing(bool value)
      {
         is_batch_drawing_ = value;
      }

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
      static constexpr int kLocationUv = 2;
      static constexpr int kLocationNormal = 3;
      inline static Color kFogColorModels = Colors::purple;

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
      std::shared_ptr<std::map<std::string, std::map<int, std::map<float, const BodyData>>>>
          model_ids_;
      std::shared_ptr<std::map<std::string_view, std::map<float, RenderID>>> timelines_;
      float global_animation_speed_ = 1.0f;
      bool is_batch_drawing_ = false;
   };
}
