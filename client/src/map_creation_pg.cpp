#if 1
#include "map_creation_pg.h"
#include "core.h"
#include "assets.h"
#include "render-models/renderer_models_v.h"
#include "render/renderer_tiles_v.h"
#include "core_c.h"
#include "core_v.h"
#include "actors.h"
#include "main_pg-adds-world_view.h"
#include "world-struct.h"
#endif

namespace Narradia
{
   void MapCreationPg::UpdateGameLogicDerived()
   {
      WorldViewAdd::get()->UpdateGameLogic();
   }
   void MapCreationPg::Finalize()
   {
      PageMngrC::get()->ChangeScene(PageNames::Main);
   }
}
