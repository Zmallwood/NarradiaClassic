#include "DoPollEvents.h"
#include "../../../core.input/model/KeyboardInput.h"
#include "../../model/Engine.h"

namespace Narradia {
    /**
     * Poll for user input events.
     */
    void DoPollEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
            case SDL_QUIT:
                Engine::Get()->set_running(false);
                break;
            case SDL_KEYDOWN:
                KeyboardInput::Get()->RegisterPressedKey(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                KeyboardInput::Get()->RegisterReleasedKey(event.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                //                MouseInput::Get()->RegisterPress(event.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                //                MouseInput::Get()->RegisterRelease(event.button.button);
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_TEXTINPUT:
                break;
            case SDL_MOUSEWHEEL:
                break;
            }
        }
    }
}
