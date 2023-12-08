#pragma once

namespace Narradia {

    /**
     * Pure abstract class inherited by all Gui components.
     */
    class GuiComponent {
      public:
        virtual void UpdateGameLogic() = 0;
    };
}
