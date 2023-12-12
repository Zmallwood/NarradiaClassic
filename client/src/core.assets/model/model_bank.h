#pragma once
#include "core.model_structure/model/model.h"
namespace Narradia
{
    class ModelBank : public Singleton<ModelBank> {
      public:
        ModelBank();
        std::shared_ptr<Model> GetModel(std::string_view model_name);

        auto models() {
            return models_;
        }
      private:
        void LoadModels();
        std::shared_ptr<Model> LoadSingleModel(std::string_view path_str);

        const std::string_view kRelModelsPath = "Resources/Models/";

        std::shared_ptr<std::map<std::string, std::shared_ptr<Model>>> models_;
    };
}
