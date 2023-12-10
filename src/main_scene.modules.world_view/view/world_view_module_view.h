#pragma once

namespace Narradia {
  class WorldViewModuleView : public Singleton<WorldViewModuleView> {
   public:
    WorldViewModuleView();
    void Render();

   private:
    std::vector<std::vector<RenderID>> rids_tiles;
    std::vector<std::vector<RenderID>> rids_tile_symbols;
  };
}
