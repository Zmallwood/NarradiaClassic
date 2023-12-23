#pragma once
namespace Narradia
{
   class WorldViewModuleView : public Singleton<WorldViewModuleView> {
     public:
      WorldViewModuleView(bool simplified_ground = false);

      void Render();

      auto render_distance() {
         return render_distance_;
      }
      void set_render_distance(int value) {
         render_distance_ = value;
      }

     private:
      void UnloadTile(int x, int y);
      void LoadTile(int x, int y);

      std::vector<std::vector<RenderID>> rids_tiles;
      std::vector<std::vector<RenderID>> rids_tile_symbols;
      int render_distance_ = 30;
      bool simplified_ground_ = false;
      const float kTinyDistance = 0.001f;
      static constexpr int kGroundSimpleK = 6;
   };
}
