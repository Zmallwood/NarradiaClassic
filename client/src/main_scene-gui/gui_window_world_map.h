#pragma once

#include "gui-core/gui_window.h"

namespace Narradia
{
   class GuiWindowWorldMap : public GuiWindow, public S<GuiWindowWorldMap>
   {
     public:
      GuiWindowWorldMap()
          : GuiWindow("World Map", {0.3f, 0.2f, 0.5f, 0.5f})
      {
      }

     private:
      void UpdateGameLogicDerived() override;
   };
}
