#if 1
#include "main_menu_pg-adds-menu_models.h"
#include "rend-core.h"
#endif

namespace Narradia
{
   void MenuModelsAdd::UpdateGameLogic() {
      {
         auto new_perspective_matrix =
             glm::perspective(glm::radians(used_fov_ / 2), 1600.0f / 900.0f, 0.1f, 1000.0f);
         CameraGL::get()->set_perspective_matrix(new_perspective_matrix);
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
}
