#include "GuiWindowCloseButton.h"
#include "Conf/Constants.h"
#include "GuiCore.h"
#include "GuiWindow.h"
#include "Pages.h"

namespace Narradia {
   GuiWindowCloseButton::~GuiWindowCloseButton() {
      if (k_verbose)
         std::cout << "Disposing GuiWindowCloseButton.\n";
   }
   void GuiWindowCloseButton::UpdateGameLogic() {
      m_hovered = false;
      if (Bounds().Contains(MousePos())) {
         Cursor::get()->set_style(CursorStyles::Hovering);
         m_hovered = true;
         MouseInput::get()->left_btn()->AddFiredAction(
             [&] {
                if (m_parentWindow->GetDestroyOnClose()) {
                   if (PageMngr::get()->curr_scene() == PageNames::Main) {
                      auto _sceneGui = MainPg::get()->scene_gui();
                      _sceneGui->RemoveGuiComponent(m_parentWindow);
                   }
                } else {
                   m_parentWindow->Hide();
                }
             },
             SDL_GetTicks() + 100);
      }
   }
   RectF GuiWindowCloseButton::Bounds() const {
      auto _width = k_width;
      auto _height = WidthToHeight(_width);
      return RectF{
          m_parentWindow->Bounds().x + m_parentWindow->Bounds().w - _width - 0.005f,
          m_parentWindow->Bounds().y + 0.03f / 2 - _height / 2, _width, _height};
   }
}
