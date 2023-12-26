#pragma once
#include "cmd/load_single_image.h"
namespace Narradia
{
   class ImageBank : public Singleton<ImageBank>
   {
     public:
      ImageBank();

      ~ImageBank();

      auto GetImage(std::string_view img_name) -> GLuint;

      auto CreateBlankTextImage(std::string unique_img_name) -> void;

     private:
      auto LoadImages() -> void;

      const std::string_view kRelImagesPath = "Resources/Images/";
      std::map<std::string, GLuint> images_;
   };
}
