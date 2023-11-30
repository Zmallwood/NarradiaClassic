#pragma once

namespace Narradia {
    /**
     * Model for IScene.
     */
    class IScene {
      public:
        void UpdateGameLogic();

      protected:
        virtual void UpdateGameLogicDerived() = 0;
    };
}
