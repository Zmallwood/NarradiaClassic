#pragma once
#include "../../common/system/typedefs.h"
#include "../../conf/model/conf.h"
#include "../../core.assets/model/image_bank.h"
#include "../../core.assets/model/model_bank.h"
#include "../../core.render.shaders/model/models_fragment.inc.cpp"
#include "../../core.render.shaders/model/models_vertex.inc.cpp"
#include "../../core.render/model/body_data.h"
#include "../../core.render/view/camera_gl.h"
#include "../../core.render/view/renderer_base_view.h"
#include "../../core.render/view/shader_program_view.h"
#include "../../matter/model/color.h"
#include "../../matter/model/colors.h"
#include "../../matter/model/point3f.h"
#include "../../matter/model/vertex3f.h"
#include "../../world.actors/model/player.h"
#include "command/new_body_keyframe.h"
#include "command/new_body_keyframe_geometry.h"
#include <glm/glm.hpp>
#include <map>
#include <string>
#include <vector>
namespace Narradia
{
   class RendererModelsView : public RendererBaseView, public Singleton<RendererModelsView> {
     public:
      RendererModelsView();
      ~RendererModelsView();
      void NewModel(std::string_view model_name);
      void DrawModel(
          std::string_view model_name, float ms_time, Point3F position, float rotation = 0.0f,
          float scaling = 1.0f, float brightness = 1.0f, glm::vec3 color_mod = {1.0f, 1.0f, 1.0f},
          bool no_fog = false, bool no_lighting = false);
      void StartBatchDrawing();
      void StopBatchDrawing();

      auto timelines() {
         return timelines_;
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
      
      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
      static constexpr int kLocationUv = 2;
      static constexpr int kLocationNormal = 3;

     private:
      inline static const Color kFogColorModels = Colors::purple;

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
      std::map<std::string, std::map<int, std::map<float, const BodyData>>> model_ids_;
      std::shared_ptr<std::map<std::string_view, std::map<float, RenderID>>> timelines_;
      float global_animation_speed_ = 1.0f;
      bool is_batch_drawing_ = false;
   };
}
