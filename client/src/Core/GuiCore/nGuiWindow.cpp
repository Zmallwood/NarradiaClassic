#include "nGuiWindow.h"
#include "Conf/Constants.h"
#include "nGuiWindowCloseButton.h"

namespace Narradia {
   // clang-format off
   GuiWindow::GuiWindow(
      StringView _title,
      RectF _bounds,
      bool _destroyOnClose,
      StringView _bgImageName)
         : GuiMovableContainer(
               {0.0f, 0.0f, _bounds.w, k_titleBarHeight},
               _bounds.GetPosition(),
               _bounds.GetSize()),
            m_closeButton(MakeShared<GuiWindowCloseButton>(this)) {
      // clang-format on
      m_bgImageName = _bgImageName;
      m_title = _title;
      m_destroyOnClose = _destroyOnClose;
   }

   GuiWindow::~GuiWindow() {
      if (k_verbose)
         std::cout << "Cleaning up GuiWindow.\n";
      m_closeButton = nullptr;
      if (k_verbose)
         std::cout << "Cleaning up of GuiWindow finished.\n";
   }

   void GuiWindow::Hide() {
      m_visible = false;
   }

   void GuiWindow::ToggleVisibility() {
      m_visible = !m_visible;
   }

   void GuiWindow::UpdateGameLogic() {
      if (!m_visible)
         return;
      m_closeButton->UpdateGameLogic();
      UpdateGameLogicDerived();
      GuiMovableContainer::UpdateGameLogic();
   }

   RectF GuiWindow::AbsTitleBarBounds() {
      return {GetPos().x, GetPos().y, GetSize().w, k_titleBarHeight};
   }
}
