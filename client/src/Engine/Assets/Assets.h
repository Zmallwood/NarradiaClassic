#pragma once

#include "Configuration/Constants.h"
#include "ModelCreation/ModelCreation.h"

namespace Narradia {

   // Model

#if 1

   class ImageBank : public Singleton<ImageBank> {
     public:
      ImageBank() {
         LoadImages();
      }

      ~ImageBank() {
         if (k_verbose)
            std::cout << "Cleaning up ImageBank\n";

         for (const auto &img : images_)
            glDeleteTextures(1, &img.second);

         if (k_verbose)
            std::cout << "Cleaning up of ImageBank finished.\n";
      }

      GLuint GetImage(StringView img_name) {
         for (auto img : images_)
            if (img.first == img_name)
               return img.second;

         return -1;
      }

      void CreateBlankTextImage(String unique_img_name) {
         GLuint tex_id;
         glGenTextures(1, &tex_id);

         images_.insert({unique_img_name, tex_id});
      }

     private:
      void LoadImages() {
         using iterator = std::filesystem::recursive_directory_iterator;

         auto all_images_path = String(SDL_GetBasePath()) + kRelImagesPath.data();

         for (auto &entry : iterator(all_images_path)) {
            auto abs_path = entry.path().string();

            if (FileExtension(abs_path) != "png")
               continue;

            auto tex_id = LoadSingleImage(abs_path);
            auto img_name = FileNameNoExt(abs_path);

            images_[img_name] = tex_id;
         }
      }

      GLuint LoadSingleImage(StringView abs_file_path) {
         GLuint tex_id;

         auto surf = IMG_Load(abs_file_path.data());

         glEnable(GL_TEXTURE_2D);
         glGenTextures(1, &tex_id);
         glBindTexture(GL_TEXTURE_2D, tex_id);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

         if (surf->format->BytesPerPixel == 4) {
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                surf->pixels);
         } else {
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                surf->pixels);
         }

         SDL_FreeSurface(surf);

         return tex_id;
      }

      const StringView kRelImagesPath = "Resources/Images/";
      Map<String, GLuint> images_;
   };

   // Show Model-structure
#if 1
   // Show Model sub classes
#if 1
   class Keyframe {
     public:
      Vector<Vertex3F> vertices;
   };

   class Timeline {
     public:
      Map<float, SharedPtr<const Keyframe>> keyframes;
   };

   class ModelPart {
     public:
      ModelPart()
          : timeline_(MakeShared<Timeline>()) {
      }

      auto texture_name() {
         return texture_name_;
      }

      void set_texture_name(String value) {
         texture_name_ = value;
      }

      auto timeline() {
         return timeline_;
      }

     private:
      String texture_name_;
      SharedPtr<Timeline> timeline_;
   };
#endif

   class Model {
     public:
      Model(int anim_duration)
          : anim_duration_(anim_duration),
            model_parts_(std::make_shared<std::vector<std::shared_ptr<ModelPart>>>()) {
      }

      auto anim_duration() {
         return anim_duration_;
      }

      auto model_parts() {
         return model_parts_;
      }

     private:
      const int anim_duration_;
      SharedPtr<Vector<SharedPtr<ModelPart>>> model_parts_;
   };
#endif

   class ModelBank : public Singleton<ModelBank> {
     public:
      ModelBank()
          : models_(MakeShared<Map<String, SharedPtr<Model>>>()) {
         LoadModels();
      }

      ~ModelBank() {
         if (k_verbose)
            std::cout << "Disposing ModelBank\n";
      }

      SharedPtr<Model> GetModel(StringView model_name) {
         return models_->at(model_name.data());
      }

      auto models() {
         return models_;
      }

     private:
      void LoadModels() {
         using iterator = std ::filesystem::recursive_directory_iterator;

         auto abs_models_path = String(SDL_GetBasePath()) + kRelModelsPath.data();

         for (const auto &entry : iterator(abs_models_path)) {
            auto abs_path = entry.path().string();

            if (FileExtension(abs_path) != "dae")
               continue;

            auto loaded_model = LoadSingleModel(abs_path);
            auto model_name = FileNameNoExt(abs_path);

            (*models_)[model_name] = loaded_model;
         }
      }

      SharedPtr<Model> LoadSingleModel(StringView path) {
         Assimp::Importer importer;
         const aiScene *raw_model = importer.ReadFile(path.data(), 0);

         return ModelCreator::get()->CreateModel(raw_model);
      }

      const StringView kRelModelsPath = "Resources/Models/";
      SharedPtr<Map<String, SharedPtr<Model>>> models_;
   };
#endif

}
