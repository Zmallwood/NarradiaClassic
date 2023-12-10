#include "LoadSingleImage.h"

namespace Narradia {
    /**
     Loads a single images with provided path, creating a GL texture and
     returning its GLuint id.
    */
    GLuint LoadSingleImage(std::string_view abs_file_path) {
        auto surface = IMG_Load(abs_file_path.data());
        glEnable(GL_TEXTURE_2D);
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        if (surface->format->BytesPerPixel == 4)
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                surface->pixels);
        else
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                surface->pixels);
        SDL_FreeSurface(surface);
        return texture_id;
    }
}
