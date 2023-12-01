#pragma once

namespace Narradia {
    class WorldDisplayModuleView : public Singleton<WorldDisplayModuleView> {
      public:
        WorldDisplayModuleView();

        void Render();
    };
}
