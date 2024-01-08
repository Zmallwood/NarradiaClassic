#include "ModelCreator.h"
#include "MeshObtainer.h"
#include "ModelPartCreator.h"

namespace Narradia {
   auto ModelCreator::ModelParts(const aiScene *_rawModel) {
      Vector<SharedPtr<ModelPart>> _allModelParts;
      for (auto &_entry : MeshObtainer::get()->ModelMeshIds(_rawModel)) {
         String _nodeName = *_entry.first;
         auto _nodeMeshIDs = _entry.second;
         for (auto &_mesh : MeshObtainer::get()->NodeMeshes(_rawModel, _nodeMeshIDs)) {
            auto _newModelPart =
                ModelPartCreator::get()->CreateModelPartFromMesh(_rawModel, _nodeName, _mesh);
            _allModelParts.push_back(_newModelPart);
         }
      }
      return _allModelParts;
   }
   auto ModelCreator::CreateModel(const aiScene *_rawModel) -> SharedPtr<Model> {
      auto _animDuration = _rawModel->mNumAnimations > 0 ? _rawModel->mAnimations[0]->mDuration : 0;
      auto _newModel = std::make_shared<Model>(_animDuration);
      for (auto &_modelPart : ModelParts(_rawModel))
         _newModel->model_parts()->push_back(_modelPart);
      return _newModel;
   }
}
