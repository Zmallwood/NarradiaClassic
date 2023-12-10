#include "GraphicsGLView.h"
#include "core.render/view/Renderer2DSolidColorsView.h"
#include "core/view/GraphicsView.h"

namespace Narradia {
    /**
     Initializes OpenGL-specific graphics parts.
    */
    GraphicsGLView::GraphicsGLView() {
        glewExperimental = GL_TRUE;
        auto glew_error = glewInit();
        if (glew_error != GLEW_OK)
            printf("Error initializing GLEW! %s\n", glewGetErrorString(glew_error));
        if (SDL_GL_SetSwapInterval(0) < 0)
            printf("Warning: Unable to disable VSync! SDL Error: %s\n", SDL_GetError());
        glClearColor(kClearColor.r, kClearColor.g, kClearColor.b, kClearColor.a);
        if (kCullFace) {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);
        }
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}
