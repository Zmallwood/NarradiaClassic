#if 1
#include "map_creation_pg_c.h"
#include "actors.h"
#include "world-struct.h"
#endif

namespace Narradia
{
   void MapCreationPgC::OnEnter()
   {
      auto map_area = World::get()->CurrWorldArea();
      auto x = map_area->GetWidth() / 2.0f;
      auto y = map_area->GetHeight() / 2.0f;
      Player::get()->set_position({x, 0.0f, y});
   }
   void MapCreationPgC::UpdateGameFlowDerived()
   {
   }
}
