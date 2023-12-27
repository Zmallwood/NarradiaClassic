#if 1
#include "map_overview_gen_scene.h"
#include "core/scene_mngr.h"
#include "assets.h"
#include "render-models/renderer_models_v.h"
#include "render/renderer_tiles_v.h"
#include "core/scene_mngr_c.h"
#include "core/graphics_v.h"
#include "main_scene-modules-world_view/camera.h"
#include "main_scene-modules-world_view/world_view_module.h"
#include "main_scene-modules-world_view/world_view_module_v.h"
#include "main_scene-modules/keyboard_movement_module.h"
#include "main_scene-modules/mouse_movement_module.h"
#include "main_scene-modules/mouse_rotation_module.h"
#include "main_scene-modules/tile_hovering_module.h"
#include "world-actors/player.h"
#include "world-struct.h"
#endif

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
      SceneMngrC::get()->ChangeScene(SceneNames::Main);
   }
}
