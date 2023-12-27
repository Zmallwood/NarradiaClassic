#include "assets.h"
#include "assets-model_creation/model_constr.h"

namespace Narradia
{
   ImageBank::ImageBank()
   {
      LoadImages();
   }
   void ImageBank::LoadImages()
   {
      using iterator = std::filesystem::recursive_directory_iterator;
      auto all_images_path = std::string(SDL_GetBasePath()) + kRelImagesPath.data();
      for (auto &entry : iterator(all_images_path))
      {
         auto abs_path = entry.path().string();
         if (FileExtension(abs_path) != "png")
            continue;
         auto tex_id = LoadSingleImage(abs_path);
         auto img_name = FileNameNoExt(abs_path);
         images_[img_name] = tex_id;
      }
   }
   GLuint ImageBank::GetImage(std::string_view img_name)
   {
      for (auto img : images_)
         if (img.first == img_name)
            return img.second;
      return -1;
   }
   void ImageBank::CreateBlankTextImage(std::string unique_img_name)
   {
      GLuint tex_id;
      glGenTextures(1, &tex_id);
      images_.insert({unique_img_name, tex_id});
   }
   ImageBank::~ImageBank()
   {
      for (const auto &img : images_)
         glDeleteTextures(1, &img.second);
   }
   GLuint ImageBank::LoadSingleImage(std::string_view abs_file_path)
   {
      GLuint tex_id;

      auto surf = IMG_Load(abs_file_path.data());

      glEnable(GL_TEXTURE_2D);
      glGenTextures(1, &tex_id);
      glBindTexture(GL_TEXTURE_2D, tex_id);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

      if (surf->format->BytesPerPixel == 4)
      {
         glTexImage2D(
             GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
             surf->pixels);
      }
      else
      {
         glTexImage2D(
             GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE,
             surf->pixels);
      }

      SDL_FreeSurface(surf);

      return tex_id;
   }
   auto ModelBank::LoadSingleModel(std::string_view path)
   {
      Assimp::Importer importer;
      const aiScene *raw_model = importer.ReadFile(path.data(), 0);
      return ModelConstr::get()->CreateModel(raw_model);
   }
   auto ModelBank::LoadModels()
   {
      using iterator = std ::filesystem::recursive_directory_iterator;
      auto abs_models_path = std::string(SDL_GetBasePath()) + kRelModelsPath.data();
      for (const auto &entry : iterator(abs_models_path))
      {
         auto abs_path = entry.path().string();
         if (FileExtension(abs_path) != "dae")
            continue;
         auto loaded_model = LoadSingleModel(abs_path);
         auto model_name = FileNameNoExt(abs_path);
         (*models_)[model_name] = loaded_model;
      }
   }
   ModelBank::ModelBank()
       : models_(std::make_shared<std::map<std::string, std::shared_ptr<Model>>>())
   {
      LoadModels();
   }
   auto ModelBank::GetModel(std::string_view model_name) -> std::shared_ptr<Model>
   {
      return models_->at(model_name.data());
   }
}
