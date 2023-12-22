#pragma once
#include "../../core-gui/model/gui_window.h"
namespace Narradia
{
   class GuiWindowWorldMap : public GuiWindow {
     public:
      GuiWindowWorldMap()
          : GuiWindow("World Map", {0.1f, 0.1f, 0.3f, 0.2f}) {
      }

     private:
      void UpdateGameLogicDerived() override;
   };
}
