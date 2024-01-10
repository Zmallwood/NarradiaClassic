#include "nGuiWindow.h"
#include "Conf/Const.h"
#include "nGuiWindowCloseButton.h"

namespace Narradia {
   // clang-format off
   nGuiWindow::nGuiWindow(
      StringView _title,
      RectF _bounds,
      bool _destroyOnClose,
      StringView _bgImageName)
         : nGuiMovableContainer(
               {0.0f, 0.0f, _bounds.w, k_titleBarHeight},
               _bounds.GetPosition(),
               _bounds.GetSize()),
            m_closeButton(MakeShared<nGuiWindowCloseButton>(this)) {
      // clang-format on
      m_bgImageName = _bgImageName;
      m_title = _title;
      m_destroyOnClose = _destroyOnClose;
   }

   nGuiWindow::~nGuiWindow() {
      if (k_verbose)
         std::cout << "Cleaning up GuiWindow.\n";
      m_closeButton = nullptr;
      if (k_verbose)
         std::cout << "Cleaning up of GuiWindow finished.\n";
   }

   void nGuiWindow::Hide() {
      m_visible = false;
   }

   void nGuiWindow::ToggleVisibility() {
      m_visible = !m_visible;
   }

   void nGuiWindow::UpdateGameLogic() {
      if (!m_visible)
         return;
      m_closeButton->UpdateGameLogic();
      UpdateGameLogicDerived();
      nGuiMovableContainer::UpdateGameLogic();
   }

   RectF nGuiWindow::AbsTitleBarBounds() {
      return {Pos().x, Pos().y, Size().w, k_titleBarHeight};
   }
}
