#pragma once
#include "../../../common/system/typedefs.h"
#include "../../../matter/model/point3f.h"
#include "../../../matter/model/vertex3f.h"
#include "../renderer_tiles_view.h"
#include <vector>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Sets geometry data for a previously created tile resource.
   ///
   /// @param[in] vao_id VAO ID for tile.
   /// @param[in] v0 Vertex 0.
   /// @param[in] v1 Vertex 1.
   /// @param[in] v2 Vertex 2.
   /// @param[in] v3 Vertex 3.
   /// @param[in] normal00 Normal 0,0.
   /// @param[in] normal10 Normal 1,0.
   /// @param[in] normal11 Normal 1,1.
   /// @param[in] normal01 Normal 0,1.
   ////////////////////////////////////////////////////////////////////////////////
   auto SetTileGeometry(
       RenderID vao_id, Vertex3F &v0, Vertex3F &v1, Vertex3F &v2, Vertex3F &v3, Point3F &normal00,
       Point3F &normal10, Point3F &normal11, Point3F &normal01) -> void;
}
