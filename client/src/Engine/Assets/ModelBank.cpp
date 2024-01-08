#include "ModelBank.h"
#include "Conf/Constants.h"
#include "ModelCreation/ModelCreator.h"
#include "ModelStructure/Model.h"

namespace Narradia {
   ModelBank::ModelBank()
       : m_models(MakeShared<Map<String, SharedPtr<Model>>>()) {
      LoadModels();
   }
   ModelBank::~ModelBank() {
      if (k_verbose)
         std::cout << "Disposing ModelBank\n";
   }
   SharedPtr<Model> ModelBank::GetModel(StringView _modelName) {
      return m_models->at(_modelName.data());
   }
   void ModelBank::LoadModels() {
      using iterator = std ::filesystem::recursive_directory_iterator;
      auto _absModelsPath = String(SDL_GetBasePath()) + k_relModelsPath.data();
      for (const auto &_entry : iterator(_absModelsPath)) {
         auto _absPath = _entry.path().string();
         if (FileExtension(_absPath) != "dae")
            continue;
         auto _loadedModel = LoadSingleModel(_absPath);
         auto _modelName = FileNameNoExt(_absPath);
         (*m_models)[_modelName] = _loadedModel;
      }
   }
   SharedPtr<Model> ModelBank::LoadSingleModel(StringView _path) {
      Assimp::Importer _importer;
      const aiScene *_rawModel= _importer.ReadFile(_path.data(), 0);
      return ModelCreator::get()->CreateModel(_rawModel);
   }
}
