#if 1
#include "map_overview_gen_scene.h"
#include "core.h"
#include "assets.h"
#include "render-models/renderer_models_v.h"
#include "render/renderer_tiles_v.h"
#include "core_c.h"
#include "core_v.h"
#include "actors.h"
#include "main_scene-adds-world_view_module.h"
#include "world-struct.h"
#endif

namespace Narradia
{
   void MapOverviewGenScene::UpdateGameLogicDerived()
   {
      WorldViewModule::get()->UpdateGameLogic();
   }
   void MapOverviewGenScene::Finalize()
   {
      SceneMngrC::get()->ChangeScene(SceneNames::Main);
   }
}
