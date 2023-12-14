#pragma once
#include "../../common/system/typedefs.h"
#include "../../conf/model/conf.h"
#include "../../core.assets/model/image_bank.h"
#include "../../core.assets/model/model_bank.h"
#include "../../core.render.shaders/model/models_fragment.inc.cpp"
#include "../../core.render.shaders/model/models_vertex.inc.cpp"
#include "../../matter/model/color.h"
#include "../../matter/model/colors.h"
#include "../../matter/model/point3f.h"
#include "../../matter/model/vertex3f.h"
#include "../../world.actors/model/player.h"
#include "../../core.render/model/body_data.h"
#include "../../core.render/view/camera_gl.h"
#include "../../core.render/view/renderer_base_view.h"
#include "../../core.render/view/shader_program_view.h"
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
      void DrawModelsMany(
          std::string_view model_name, float ms_time, std::vector<Point3F> positions,
          std::vector<float> rotations, std::vector<float> scalings,
          std::vector<float> brightnesses, std::vector<glm::vec3> color_mods);
      void StartBatchDrawing();
      void StopBatchDrawing();

     private:
      RenderID NewBodyKeyframe(std::string_view model_name, float ms_time, int num_vertices);
      void NewBodyKeyframeGeometry(
          std::string_view image_name, float ms_time, GLuint vao_id,
          std::vector<Vertex3F> vertices, std::vector<Point3F> vertex_normals);

      inline static const Color kFogColorModels = Colors::purple;
      const int kLocationPosition = 0;
      const int kLocationColor = 1;
      const int kLocationUv = 2;
      const int kLocationNormal = 3;

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
      std::map<std::string_view, std::map<float, RenderID>> timelines_;
      float global_animation_speed_ = 1.0f;
      bool is_batch_drawing_ = false;
   };
}
