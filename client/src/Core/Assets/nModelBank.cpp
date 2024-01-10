#include "nModelBank.h"
#include "Conf/Const.h"
#include "ModelCreation/nModelCreator.h"
#include "ModelStructure/nModel.h"

namespace Narradia {
   nModelBank::nModelBank()
       : m_models(MakeShared<Map<String, SharedPtr<nModel>>>()) {
      LoadModels();
   }

   nModelBank::~nModelBank() {
      if (k_verbose)
         std::cout << "Disposing ModelBank\n";
   }

   SharedPtr<nModel> nModelBank::GetModel(StringView _modelName) {
      return m_models->at(_modelName.data());
   }

   void nModelBank::LoadModels() {
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

   SharedPtr<nModel> nModelBank::LoadSingleModel(StringView _path) {
      Assimp::Importer _importer;
      const aiScene *_rawModel= _importer.ReadFile(_path.data(), 0);
      return nModelCreator::get()->CreateModel(_rawModel);
   }
}
