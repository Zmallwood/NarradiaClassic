#include "poll_events.h"
namespace Narradia
{
   SDL_Event ev;

   auto PollEvents() -> void {
      while (SDL_PollEvent(&ev) != 0) {
         switch (ev.type) {
         case SDL_QUIT:
            Engine::get()->set_running(false);
            break;
         case SDL_KEYDOWN:
            KbInput::get()->OnKeyPress(ev.key.keysym.sym);
            break;
         case SDL_KEYUP:
            KbInput::get()->OnKeyRelease(ev.key.keysym.sym);
            break;
         case SDL_MOUSEBUTTONDOWN:
            MouseInput::get()->OnPress(ev.button.button);
            break;
         case SDL_MOUSEBUTTONUP:
            MouseInput::get()->OnRelease(ev.button.button);
            break;
         case SDL_MOUSEMOTION:
            break;
         case SDL_TEXTINPUT:
            KbInput::get()->AppendTextInput(ev.text.text);
            break;
         case SDL_MOUSEWHEEL:
            break;
         }
      }
   }
}