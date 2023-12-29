#if 1
#include "map_creation_pg_v.h"
#include "map_creation_pg-adds-map_gen_v.h"
#endif

namespace Narradia
{
   void MapCreationPgV::RenderDerived()
   {
       MapGenAddV::get()->Render();
   }
}
