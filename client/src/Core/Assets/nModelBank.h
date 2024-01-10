#pragma once

namespace Narradia {
   class nModel;

   class nModelBank : public Singleton<nModelBank> {
     public:
      nModelBank();
      ~nModelBank();
      SharedPtr<nModel> GetModel(StringView _modelName);

      auto GetModels() {
         return m_models;
      }

     private:
      void LoadModels();
      SharedPtr<nModel> LoadSingleModel(StringView _path);

      const StringView k_relModelsPath = "Resources/Models/";
      SharedPtr<Map<String, SharedPtr<nModel>>> m_models;
   };
}
