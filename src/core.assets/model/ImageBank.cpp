#include "ImageBank.h"
#include "core/model/Graphics.h"
#include "functions/FileUtilities.h"

namespace Narradia {
    ImageBank::ImageBank() {
        LoadImages();
    }

    void ImageBank::LoadImages() {
        using iterator = std::filesystem::recursive_directory_iterator;
        auto abs_all_images_path =
            std::string(SDL_GetBasePath()) + kRelImagesPath.data();

        for (auto &imageFileEntry : iterator(abs_all_images_path)) {
            auto abs_file_path = imageFileEntry.path().string();
            if (GetFileExtension(abs_file_path) != "png")
                continue;
            auto texture_id = LoadSingleImage(abs_file_path);
            auto image_name = std::string(GetFileNameNoExt(abs_file_path));
            images_.insert({image_name, texture_id});
        }
    }

    GLuint ImageBank::LoadSingleImage(std::string_view abs_file_path) {
        auto surface = IMG_Load(abs_file_path.data());
        glEnable(GL_TEXTURE_2D);
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        if (surface->format->BytesPerPixel == 4)
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA,
                GL_UNSIGNED_BYTE, surface->pixels);
        else
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB,
                GL_UNSIGNED_BYTE, surface->pixels);
        SDL_FreeSurface(surface);

        return texture_id;
    }

    GLuint ImageBank::GetImage(std::string_view image_name) {
        for (auto image : images_)
            if (image.first == image_name)
                return image.second;

        return -1;
    }

    ImageBank::~ImageBank() {
        for (const auto &image : images_)
            glDeleteTextures(1, &image.second);
    }
}
