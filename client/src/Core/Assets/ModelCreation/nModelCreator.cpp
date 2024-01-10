#include "nModelCreator.h"
#include "nMeshObtainer.h"
#include "nModelPartCreator.h"
#include "Core/Assets/nModelBank.h"
#include "Core/Assets/ModelStructure/nModel.h"

namespace Narradia {
   auto nModelCreator::ModelParts(const aiScene *_rawModel) {
      Vec<SharedPtr<nModelPart>> _allModelParts;
      for (auto &_entry : nMeshObtainer::get()->ModelMeshIds(_rawModel)) {
         String _nodeName = *_entry.first;
         auto _nodeMeshIDs = _entry.second;
         for (auto &_mesh : nMeshObtainer::get()->NodeMeshes(_rawModel, _nodeMeshIDs)) {
            auto _newModelPart =
                nModelPartCreator::get()->CreateModelPartFromMesh(_rawModel, _nodeName, _mesh);
            _allModelParts.push_back(_newModelPart);
         }
      }
      return _allModelParts;
   }

   auto nModelCreator::CreateModel(const aiScene *_rawModel) -> SharedPtr<nModel> {
      auto _animDuration = _rawModel->mNumAnimations > 0 ? _rawModel->mAnimations[0]->mDuration : 0;
      auto _newModel = MakeShared<nModel>(_animDuration);
      for (auto &_modelPart : ModelParts(_rawModel))
         _newModel->ModelParts()->push_back(_modelPart);
      return _newModel;
   }
}
