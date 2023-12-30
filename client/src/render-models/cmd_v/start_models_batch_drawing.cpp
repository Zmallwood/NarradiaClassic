#if 1
#include "start_models_batch_drawing.h"
#include "render-models/renderer_models_v.h"
#include "render/camera_gl.h"
#include "render/shader_program.h"
#include "render/shader_program_v.h"
#endif

namespace Narradia
{
   auto StartModelsBatchDrawing() -> void {
      auto renderer = RendererModelsV::get();
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
