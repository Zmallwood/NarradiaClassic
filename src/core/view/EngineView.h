#pragma once

namespace Narradia
{
    /**
     View for Engine.
    */
    class EngineView : public Singleton<EngineView> {
      public:
        void Render();
    };
}
