#pragma once

namespace Narradia {
    class WorldDisplayModuleView : public Singleton<WorldDisplayModuleView> {
      public:
        void Render();
    };
}