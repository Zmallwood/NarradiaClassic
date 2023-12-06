#pragma once

namespace Narradia {
    class WorldDisplayModuleView : public Singleton<WorldDisplayModuleView> {
      public:
        WorldDisplayModuleView();

        void Render();

      private:
        std::vector<std::vector<RenderId>> rids_ground;
        std::vector<std::vector<RenderId>> rids_objects;
    };
}
