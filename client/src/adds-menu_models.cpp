#if 1
#include "adds-menu_models.h"
#include "rend-core.h"
#include "rend_models_v.h"
#endif

namespace Narradia
{
   // Model
#if 1
   void MenuModelsAdd::UpdateGameLogic() {
      {
         auto new_persp_matrix =
             glm::perspective(glm::radians(used_fov_ / 2), 1600.0f / 900.0f, 0.1f, 1000.0f);
         CameraGL::get()->set_persp_matrix(new_persp_matrix);
      }
      {
         auto look_from = Point3F{0.0f, 5.0f, -8.0f};
         auto look_at = Point3F{0.0f, 3.0f, 0.0f};
         auto new_view_matrix = glm::lookAt(
             glm::vec3(look_from.x, look_from.y, look_from.z),
             glm::vec3(look_at.x, look_at.y, look_at.z), glm::vec3(0.0, 1.0, 0.0));
         CameraGL::get()->set_view_matrix(new_view_matrix);
      }
   }
#endif

   // View
#if 1
   void MenuModelsAddV::Render() {
      DrawModel("Player2", SDL_GetTicks(), {-3.0f, 0.0f, 0.0f});
      //DrawModel("MobBoar", SDL_GetTicks(), {3.0f, 1.0f, 0.0f}, 0.0f, 0.7f);
   }
#endif
}
