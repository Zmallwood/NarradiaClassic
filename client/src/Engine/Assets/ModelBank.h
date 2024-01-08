#pragma once

namespace Narradia {
   class Model;

   class ModelBank : public Singleton<ModelBank> {
     public:
      ModelBank();
      ~ModelBank();
      SharedPtr<Model> GetModel(StringView _modelName);
      auto Models() {
         return m_models;
      }

     private:
      void LoadModels();
      SharedPtr<Model> LoadSingleModel(StringView _path);

      const StringView k_relModelsPath = "Resources/Models/";
      SharedPtr<Map<String, SharedPtr<Model>>> m_models;
   };
}
