#include "MeshObtainer.h"

namespace Narradia {
   auto MeshObtainer::ModelMeshIds(const aiScene *_rawModel) const
       -> Map<SharedPtr<String>, Vec<int>> {
      Map<SharedPtr<String>, Vec<int>> _nodeNameToMeshes;
      auto _rootNode = _rawModel->mRootNode;
      auto _numSubNodes = _rootNode->mNumChildren;
      for (auto _i = 0; _i < _numSubNodes; _i++) {
         auto _subNode = _rootNode->mChildren[_i];
         auto _subNode_name = _subNode->mName;
         auto _numMeshes = _subNode->mNumMeshes;
         Vec<int> _meshes;
         for (auto _j = 0; _j < _numMeshes; _j++)
            _meshes.push_back(_subNode->mMeshes[_j]);
         const char *_cStr = _subNode_name.C_Str();
         auto _key = String{_cStr};
         _nodeNameToMeshes.insert({MakeShared<String>(_key), _meshes});
      }
      return _nodeNameToMeshes;
   }
   auto MeshObtainer::NodeMeshes(const aiScene *_rawModel, Vec<int> _nodeMeshIDs) const
       -> Vec<aiMesh *> {
      Vec<aiMesh *> _nodeMeshes;
      auto _numMeshes = _nodeMeshIDs.size();
      for (auto _i = 0; _i < _numMeshes; _i++) {
         auto _mesh = _rawModel->mMeshes[_nodeMeshIDs.at(_i)];
         _nodeMeshes.push_back(_mesh);
      }
      return _nodeMeshes;
   }
}
