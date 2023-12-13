#include "graphics_view.h"
#include "core/model/engine.h"
#include "core/model/graphics.h"
#include "graphics_gl_view.h"
namespace Narradia
{
    /**
     Initialize SDL window and some of the OpenGL settings.
    */
    GraphicsView::GraphicsView() {
        auto window_size = Graphics::get()->win_size();
        auto window_flags = Graphics::get()->win_flags();
        auto window = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow(
                Engine::get()->title().data(), 0, 0, window_size.w, window_size.h,
                window_flags),
            SDLDeleter());
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        if (SDL_GL_CreateContext(window.get()) == nullptr) {
            std::cout << "OpenGL context could not be "
                         "created! SDL Error: "
                      << std::string(SDL_GetError()) << std::endl;
            return;
        }
        Graphics::get()->set_win(window);
        GraphicsGLView::Touch();
    }

    /**
     Clear canvas in the beginning of each new frame.
    */
    void GraphicsView::ClearCanvas() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /**
     Present canvas to the screen at the end of each frame.
    */
    void GraphicsView::PresentCanvas() {
        SDL_GL_SwapWindow(Graphics::get()->win().get());
    }
}