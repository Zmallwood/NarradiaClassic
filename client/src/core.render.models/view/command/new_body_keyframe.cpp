#include "new_body_keyframe.h"
namespace Narradia
{
   RenderID NewBodyKeyframe(std::string_view model_name, float ms_time, int num_vertices) {
      auto renderer = RendererModelsView::get();
      auto renderer_base = renderer->renderer_base();
      auto timelines = renderer->timelines();
      auto vao_id = renderer_base->GenNewVAOId();
      if (timelines->count(model_name) == 0)
         timelines->insert({model_name, std::map<float, RenderID>()});
      timelines->at(model_name).insert({ms_time, vao_id});
      return vao_id;
   }
}
