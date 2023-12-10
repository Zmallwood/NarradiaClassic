#include "ImageBank.h"
#include "command/FileUtilities.h"
#include "command/LoadSingleImage.h"
#include "core/model/Graphics.h"

namespace Narradia {
    /**
     Load images on first use.
    */
    ImageBank::ImageBank() {
        LoadImages();
    }

    /**
     Loads all images in images path, creating GL textures and storing their
     ids as GLuints.
    */
    void ImageBank::LoadImages() {
        using iterator = std::filesystem::recursive_directory_iterator;
        auto abs_all_images_path = std::string(SDL_GetBasePath()) + kRelImagesPath.data();
        for (auto &imageFileEntry : iterator(abs_all_images_path)) {
            auto abs_file_path = imageFileEntry.path().string();
            if (GetFileExtension(abs_file_path) != "png")
                continue;
            auto texture_id = LoadSingleImage(abs_file_path);
            auto image_name = std::string(GetFileNameNoExt(abs_file_path));
            images_.insert({image_name, texture_id});
        }
    }

    /**
     Returns the GLuint id corresponding to the provided image name:
    */
    GLuint ImageBank::GetImage(std::string_view image_name) {
        for (auto image : images_)
            if (image.first == image_name)
                return image.second;
        return -1;
    }

    /**
     Creates a blank GL texture used for rendering text on.
    */
    void ImageBank::CreateBlankTextImage(std::string unique_image_name) {
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        images_.insert({unique_image_name, texture_id});
    }

    /**
     Cleanup on class disposal.
    */
    ImageBank::~ImageBank() {
        for (const auto &image : images_)
            glDeleteTextures(1, &image.second);
    }
}
