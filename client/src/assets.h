#pragma once

#include "conf.h"
#include "model_mk.h"

namespace Narradia
{
   class ImageBank : public S<ImageBank> {
     public:
      ImageBank() {

         LoadImages();
      }

      ~ImageBank() {

         if (kVerbose)
            std::cout << "Cleaning up ImageBank\n";

         for (const auto &img : images_)
            glDeleteTextures(1, &img.second);

         if (kVerbose)
            std::cout << "Cleaning up of ImageBank finished.\n";
      }

      GLuint GetImage(std::string_view img_name) {

         for (auto img : images_)
            if (img.first == img_name)
               return img.second;

         return -1;
      }

      void CreateBlankTextImage(std::string unique_img_name) {

         GLuint tex_id;
         glGenTextures(1, &tex_id);

         images_.insert({unique_img_name, tex_id});
      }

     private:
      void LoadImages() {

         using iterator = std::filesystem::recursive_directory_iterator;

         auto all_images_path = std::string(SDL_GetBasePath()) + kRelImagesPath.data();

         for (auto &entry : iterator(all_images_path)) {

            auto abs_path = entry.path().string();

            if (FileExtension(abs_path) != "png")
               continue;

            auto tex_id = LoadSingleImage(abs_path);
            auto img_name = FileNameNoExt(abs_path);

            images_[img_name] = tex_id;
         }
      }

      GLuint LoadSingleImage(std::string_view abs_file_path) {

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
         }
         else {

            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                surf->pixels);
         }

         SDL_FreeSurface(surf);

         return tex_id;
      }

      const std::string_view kRelImagesPath = "Resources/Images/";
      std::map<std::string, GLuint> images_;
   };

   // Show Model-structure
#if 1
   // Show Model sub classes
#if 1
   class Keyframe {
     public:
      std::vector<Vertex3F> vertices;
   };

   class Timeline {
     public:
      std::map<float, std::shared_ptr<const Keyframe>> keyframes;
   };

   class ModelPart {
     public:
      ModelPart()
          : timeline_(std::make_shared<Timeline>()) {
      }

      auto texture_name() {
         return texture_name_;
      }

      void set_texture_name(std::string value) {
         texture_name_ = value;
      }

      auto timeline() {
         return timeline_;
      }

     private:
      std::string texture_name_;
      std::shared_ptr<Timeline> timeline_;
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
      std::shared_ptr<std::vector<std::shared_ptr<ModelPart>>> model_parts_;
   };
#endif

   class ModelBank : public S<ModelBank> {
     public:
      ModelBank()
          : models_(std::make_shared<std::map<std::string, std::shared_ptr<Model>>>()) {
         LoadModels();
      }

      ~ModelBank() {
         if (kVerbose)
            std::cout << "Disposing ModelBank\n";
      }

      auto GetModel(std::string_view model_name) -> std::shared_ptr<Model> {
         return models_->at(model_name.data());
      }

      auto models() {
         return models_;
      }

     private:
      void LoadModels() {

         using iterator = std ::filesystem::recursive_directory_iterator;

         auto abs_models_path = std::string(SDL_GetBasePath()) + kRelModelsPath.data();

         for (const auto &entry : iterator(abs_models_path)) {

            auto abs_path = entry.path().string();

            if (FileExtension(abs_path) != "dae")
               continue;

            auto loaded_model = LoadSingleModel(abs_path);
            auto model_name = FileNameNoExt(abs_path);

            (*models_)[model_name] = loaded_model;
         }
      }

      std::shared_ptr<Model> LoadSingleModel(std::string_view path) {
         Assimp::Importer importer;
         const aiScene *raw_model = importer.ReadFile(path.data(), 0);
         return ModelCreator::get()->CreateModel(raw_model);
      }

      const std::string_view kRelModelsPath = "Resources/Models/";
      std::shared_ptr<std::map<std::string, std::shared_ptr<Model>>> models_;
   };
}
