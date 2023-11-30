#pragma once

namespace Narradia {

    class ImageBank : public Singleton<ImageBank> {
      public:
        ImageBank();

        SDL_Texture *GetImage(std::string_view image_name);

      private:
        void LoadImages();

        std::shared_ptr<SDL_Texture>
        LoadSingleImage(std::string_view abs_file_path);

        const std::string_view kRelImagesPath = "Resources/Images/";
        std::map<std::string, std::shared_ptr<SDL_Texture>> images_;
    };
}