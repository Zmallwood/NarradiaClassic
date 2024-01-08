#pragma once

namespace Narradia {
   RenderID NewTile();
   RenderID NewTileSurface();
   void SetTileGeom(RenderID _VAOID, Square<Vertex3F> &_verts);
   void SetTileSufaceGeom(RenderID _VAOID, Vec<Vec<Square<Vertex3F>>> &_verts);
   void DrawTileSurface(StringView _imgName, RenderID _VAOID, bool _depthTestOff = false);
   void DrawTile(StringView _imgName, RenderID _VAOID, bool _depthTestOff = false);
   void StartTileBatchDrawing();
   void StopTileBatchDrawing();
}
