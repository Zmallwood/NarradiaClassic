#pragma once

namespace Narradia {
    class FPSCounterModuleView : public Singleton<FPSCounterModuleView> {
      public:
        FPSCounterModuleView();

        void Render();

      private:
        RenderId rid_text;
    };
}
