#pragma once

namespace Narradia {
    class WorldViewModuleView : public Singleton<WorldViewModuleView> {
      public:
        WorldViewModuleView();

        void Render();

      private:
        std::vector<std::vector<RenderId>> rids_tiles;
        float camera_height_ = 3.0f;
    };
}
