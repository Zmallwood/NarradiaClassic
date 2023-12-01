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
            auto image = LoadSingleImage(abs_file_path);
            images_.insert(
                {std::string(GetFileNameNoExt(abs_file_path)), image});
        }
    }

    std::shared_ptr<SDL_Texture>
    ImageBank::LoadSingleImage(std::string_view abs_file_path) {
        //        auto surface = IMG_Load(abs_file_path.data());
        //        auto texture = std::shared_ptr<SDL_Texture>(
        //            SDL_CreateTextureFromSurface(
        //                Graphics::Get()->renderer().get(), surface),
        //            SDLDeleter());
        //        SDL_FreeSurface(surface);
        //
        //        return texture;
        return nullptr;
    }

    SDL_Texture *ImageBank::GetImage(std::string_view image_name) {
        for (auto image : images_)
            if (image.first == image_name)
                return image.second.get();

        return nullptr;
    }
}
