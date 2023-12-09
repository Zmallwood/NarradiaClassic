#pragma once

namespace Narradia
{
    /**
     Controller for Engine.
    */
    class EngineController : public Singleton<EngineController> {
      public:
        void HandleInput();
        void UpdateGameFlow();
    };
}
