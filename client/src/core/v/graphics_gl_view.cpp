#include "graphics_gl_view.h"

namespace Narradia
{
   GraphicsGLView::GraphicsGLView()
   {
      glewExperimental = GL_TRUE;
      auto glew_error = glewInit();
      if (glew_error != GLEW_OK)
         std::cout << "Error initializing GLEW: " << glewGetErrorString(glew_error) << std::endl;
      if (SDL_GL_SetSwapInterval(0) < 0)
         std::cout << "Warning: Unable to disable VSync, SDL Error: " << SDL_GetError()
                   << std::endl;
      glClearColor(kClearColor.r, kClearColor.g, kClearColor.b, kClearColor.a);
      if (kCullFace)
      {
         glEnable(GL_CULL_FACE);
         glCullFace(GL_FRONT);
      }
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   }
}
