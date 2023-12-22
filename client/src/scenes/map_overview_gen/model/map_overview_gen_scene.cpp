#include "map_overview_gen_scene.h"
#include "main_scene-modules-world_view/model/world_view_module.h"
#include "world-actors/model/player.h"
#include "main_scene-modules/model/keyboard_movement_module.h"
#include "main_scene-modules/model/mouse_movement_module.h"
#include "main_scene-modules/model/mouse_rotation_module.h"
#include "main_scene-modules/model/tile_hovering_module.h"
#include "../../../core/model/scene_mngr.h"
#include "world-structure/model/world.h"
#include "core-assets/model/image_bank.h"
#include "core/view/graphics_view.h"
#include "core-render/view/renderer_tiles_view.h"
#include "core-render-models/view/renderer_models_view.h"
#include "main_scene-modules-world_view/view/world_view_module_view.h"
#include "main_scene-modules-world_view/model/camera.h"
namespace Narradia
{
   void MapOverviewGenScene::UpdateGameLogicDerived() {
      KeyboardMovementModule::get()->UpdateGameLogic();
      MouseMovementModule::get()->UpdateGameLogic();
      WorldViewModule::get()->UpdateGameLogic();
      MouseRotationModule::get()->UpdateGameLogic();
      TileHoveringModule::get()->UpdateGameLogic();
   }


   void MapOverviewGenScene::Finalize() {
       SceneMngr::get()->set_curr_scene(SceneNames::Main);
   }
}
