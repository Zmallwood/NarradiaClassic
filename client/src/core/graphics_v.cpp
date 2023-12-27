#if 1
#include "graphics_v.h"
#include "core/engine.h"
#include "core/graphics.h"
#include "graphics_gl_v.h"
#endif

namespace Narradia
{
   GraphicsV::GraphicsV()
   {
      auto win_size = Graphics::get()->win_size();
      auto win_flags = Graphics::get()->win_flags();
      auto win = std::shared_ptr<SDL_Window>(
          SDL_CreateWindow(Engine::get()->title().data(), 0, 0, win_size.w, win_size.h, win_flags),
          SDLDeleter());
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
      if (SDL_GL_CreateContext(win.get()) == nullptr)
      {
         std::cout << "OpenGL context could not be "
                      "created! SDL Error: "
                   << std::string(SDL_GetError()) << std::endl;
         return;
      }
      Graphics::get()->set_win(win);
      GraphicsGLV::Touch();
   }
   void GraphicsV::ClearCanvas()
   {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   }
   void GraphicsV::PresentCanvas()
   {
      SDL_GL_SwapWindow(Graphics::get()->win().get());
   }
}
