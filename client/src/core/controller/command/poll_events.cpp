#include "poll_events.h"
#include "core.input/model/keyboard_input.h"
#include "core.input/model/mouse_input.h"
#include "core/model/engine.h"
namespace Narradia
{
    /**
     Poll for user input events.
    */
    void PollEvents() {
        SDL_Event ev;
        while (SDL_PollEvent(&ev) != 0) {
            switch (ev.type) {
            case SDL_QUIT:
                Engine::Get()->set_running(false);
                break;
            case SDL_KEYDOWN:
                KeyboardInput::Get()->OnKeyPress(ev.key.keysym.sym);
                break;
            case SDL_KEYUP:
                KeyboardInput::Get()->OnKeyRelease(ev.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                MouseInput::Get()->OnPress(ev.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                MouseInput::Get()->OnRelease(ev.button.button);
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_TEXTINPUT:
                KeyboardInput::Get()->AppendTextInput(ev.text.text);
                break;
            case SDL_MOUSEWHEEL:
                break;
            }
        }
    }
}
