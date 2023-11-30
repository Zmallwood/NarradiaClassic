#include "GraphicsView.h"
#include "../model/Engine.h"
#include "../model/Graphics.h"

namespace Narradia {
    /**
     * Initialize SDL window and renderer.
     */
    GraphicsView::GraphicsView() {
        auto window_size = Graphics::Get()->window_size();
        auto window_flags = Graphics::Get()->window_flags();

        auto window = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow(
                Engine::Get()->title().data(), 0, 0, window_size.width,
                window_size.height, window_flags),
            SDLDeleter());

        auto renderer = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED),
            SDLDeleter());

        Graphics::Get()->set_window(window);
        Graphics::Get()->set_renderer(renderer);
    }

    /**
     * Clear canvas in the beginning of each new frame.
     */
    void GraphicsView::ClearCanvas() {
        auto renderer = Graphics::Get()->renderer();
        auto clear_color = Graphics::Get()->clear_color();
        SDL_SetRenderDrawColor(
            renderer.get(), clear_color.r, clear_color.g, clear_color.b, 255);
        SDL_RenderClear(renderer.get());
    }

    /**
     * Present canvas to the screen at the end of each frame.
     */
    void GraphicsView::PresentCanvas() {
        SDL_RenderPresent(Graphics::Get()->renderer().get());
    }
}
