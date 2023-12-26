#include "image_bank.h"
#include "cmd/file_utilities.h"
#include <string_view>
namespace Narradia
{
   using iterator = std::filesystem::recursive_directory_iterator;

   static GLuint tex_id;

   ImageBank::ImageBank()
   {
      LoadImages();
   }

   auto ImageBank::LoadImages() -> void
   {
      auto all_images_path = std::string(SDL_GetBasePath()) + kRelImagesPath.data();
      for (auto &entry : iterator(all_images_path))
      {
         auto abs_path = entry.path().string();
         if (FileExtension(abs_path) != "png")
            continue;
         tex_id = LoadSingleImage(abs_path);
         auto img_name = FileNameNoExt(abs_path);
         images_[img_name] = tex_id;
      }
   }

   auto ImageBank::GetImage(std::string_view img_name) -> GLuint
   {
      for (auto img : images_)
         if (img.first == img_name)
            return img.second;
      return -1;
   }

   auto ImageBank::CreateBlankTextImage(std::string unique_img_name) -> void
   {
      glGenTextures(1, &tex_id);
      images_.insert({unique_img_name, tex_id});
   }

   ImageBank::~ImageBank()
   {
      for (const auto &img : images_)
         glDeleteTextures(1, &img.second);
   }
}
