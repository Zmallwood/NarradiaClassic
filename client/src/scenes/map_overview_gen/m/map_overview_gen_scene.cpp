#include "map_overview_gen_scene.h"
#include "core/m/scene_mngr.h"
#include "assets/m/image_bank.h"
#include "render-models/v/renderer_models_view.h"
#include "render/v/renderer_tiles_view.h"
#include "core/c/scene_mngr_controller.h"
#include "core/v/graphics_view.h"
#include "main_scene-modules-world_view/m/camera.h"
#include "main_scene-modules-world_view/m/world_view_module.h"
#include "main_scene-modules-world_view/v/world_view_module_view.h"
#include "main_scene-modules/m/keyboard_movement_module.h"
#include "main_scene-modules/m/mouse_movement_module.h"
#include "main_scene-modules/m/mouse_rotation_module.h"
#include "main_scene-modules/m/tile_hovering_module.h"
#include "world-actors/m/player.h"
#include "world-struct/m/world.h"

namespace Narradia
{
   void MapOverviewGenScene::UpdateGameLogicDerived()
   {
      KeyboardMovementModule::get()->UpdateGameLogic();
      MouseMovementModule::get()->UpdateGameLogic();
      WorldViewModule::get()->UpdateGameLogic();
      MouseRotationModule::get()->UpdateGameLogic();
      TileHoveringModule::get()->UpdateGameLogic();
   }

   void MapOverviewGenScene::Finalize()
   {
      SceneMngrController::get()->ChangeScene(SceneNames::Main);
   }
}
