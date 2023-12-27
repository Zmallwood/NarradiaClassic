#if 1
#include "renderer_models_view.h"
#include "shaders/m/models_fragment.inc.cpp"
#include "shaders/m/models_vertex.inc.cpp"
#include "render/v/shader_program_view.h"
#endif

namespace Narradia
{
   RendererModelsView::RendererModelsView()
       : timelines_(std::make_shared<std::map<std::string_view, std::map<float, RenderID>>>()),
         model_ids_(std::make_shared<
                    std::map<std::string, std::map<int, std::map<float, const BodyData>>>>())
   {
      shader_program_view()->Create(vertex_shader_source_models, fragment_shader_source_models);
      location_view_ = GetUniformLocation("view");
      location_projection_ = GetUniformLocation("projection");
      location_alpha_ = GetUniformLocation("mAlpha");
      location_model_ = GetUniformLocation("model");
      location_model_no_translation_ = GetUniformLocation("modelNoTranslation");
      location_color_mod_ = GetUniformLocation("mColorMod");
      location_view_pos_ = GetUniformLocation("viewPos");
      location_fog_color_ = GetUniformLocation("fogColor");
      location_no_fog_ = GetUniformLocation("noFog");
      location_no_lighting_ = GetUniformLocation("noLighting");
   }

   RendererModelsView::~RendererModelsView()
   {
      CleanupBase();
   }
}
