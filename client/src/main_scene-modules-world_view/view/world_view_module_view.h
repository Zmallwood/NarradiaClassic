#pragma once
namespace Narradia
{
   class WorldViewModuleView : public Singleton<WorldViewModuleView> {
     public:
      WorldViewModuleView();
      void Render();

      auto render_distance() {
         return render_distance_;
      }
      void set_render_distance(int value) {
         render_distance_ = value;
      }

     private:
      std::vector<std::vector<RenderID>> rids_tiles;
      std::vector<std::vector<RenderID>> rids_tile_symbols;
      int render_distance_ = 30;
      const float kTinyDistance = 0.001f;
   };
}
