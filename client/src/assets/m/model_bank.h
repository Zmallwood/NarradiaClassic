#pragma once

#include "assets-model_creation/m/model_constr.h"
#include "model.h"

namespace Narradia
{
   class ModelBank : public Singleton<ModelBank>
   {
     public:
      ModelBank();

      auto GetModel(std::string_view model_name) -> std::shared_ptr<Model>;

      auto models()
      {
         return models_;
      }

     private:
      auto LoadModels();

      auto LoadSingleModel(std::string_view path);

      const std::string_view kRelModelsPath = "Resources/Models/";
      std::shared_ptr<std::map<std::string, std::shared_ptr<Model>>> models_;
   };
}
