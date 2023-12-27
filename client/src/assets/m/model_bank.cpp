#if 1
#include "model_bank.h"
#include "assets-model_creation/m/model_constr.h"
#include "model.h"
#endif

namespace Narradia
{
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
