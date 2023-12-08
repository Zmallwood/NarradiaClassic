#pragma once

namespace Narradia {
    /**
     * Loads, holds and provides images from image folder on file system.
     */
    class ImageBank : public Singleton<ImageBank> {
      public:
        ImageBank();
        ~ImageBank();
        GLuint GetImage(std::string_view image_name);
        void CreateBlankTextImage(std::string unique_image_name);

      private:
        void LoadImages();

        const std::string_view kRelImagesPath = "Resources/Images/";
        std::map<std::string, GLuint> images_;
    };
}
