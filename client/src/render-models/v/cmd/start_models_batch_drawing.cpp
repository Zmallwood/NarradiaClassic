#include "start_models_batch_drawing.h"

namespace Narradia
{
   auto StartModelsBatchDrawing() -> void
   {
      auto renderer = RendererModelsView::get();
      renderer->set_is_batch_drawing(true);
      glEnable(GL_DEPTH_TEST);
      glUseProgram(renderer->shader_program_view()->shader_program()->program_id());
      glUniformMatrix4fv(
          renderer->location_projection(), 1, GL_FALSE,
          value_ptr(CameraGL::get()->perspective_matrix()));
      glUniformMatrix4fv(
          renderer->location_view(), 1, GL_FALSE, glm::value_ptr(CameraGL::get()->view_matrix()));
   }
}
