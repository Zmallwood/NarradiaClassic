#pragma once

namespace Narradia {
    class MouseRotationModule : public Singleton<MouseRotationModule> {
      public:
        void UpdateGameLogic();
    };
}
