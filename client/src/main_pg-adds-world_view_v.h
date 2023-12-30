#pragma once

namespace Narradia
{
   class Tile;

   class WorldViewAddV : public S<WorldViewAddV> {
     public:
      WorldViewAddV(bool simplified_ground = false);
      void Render();
      void InitCurrWorldArea();
      auto render_distance() {
         return render_distance_;
      }
      void set_render_distance(int value) {
         render_distance_ = value;
      }

     private:
      void DrawGround(std::shared_ptr<Tile> tile, Point coord);
      void DrawMob(std::shared_ptr<Tile> tile, Point coord);
      void DrawObjects(std::shared_ptr<Tile> tile, Point coord);
      void DrawPlayer();
      void DrawTileSymbols(std::shared_ptr<Tile> tile, Point coord);

      std::vector<std::vector<RenderID>> rids_tiles;
      std::vector<std::vector<RenderID>> rids_tile_symbols;
      int render_distance_ = 30;
      bool simplified_ground_ = false;
      const float kTinyDistance = 0.001f;
      static constexpr int kGroundSimpleK = 6;
   };
}
