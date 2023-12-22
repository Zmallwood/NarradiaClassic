#include "gui_container.h"
namespace Narradia
{
   void GuiContainer::UpdateGameLogic() {
      for (auto &comp : gui_components_)
         comp->UpdateGameLogic();
   }

   void GuiContainer::AddGuiComponent(std::shared_ptr<GuiComponent> comp) {
       gui_components_.push_back(comp);
   }
}
