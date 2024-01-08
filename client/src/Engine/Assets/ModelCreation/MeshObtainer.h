#pragma once

namespace Narradia {
   class MeshObtainer : public Singleton<MeshObtainer> {
     public:
      // clang-format off
      auto ModelMeshIds(
              const aiScene *_rawModel) const
                 -> Map<SharedPtr<String>, Vec<int>>;
      auto NodeMeshes(
              const aiScene *_rawModel,
              Vec<int> _nodeMeshIDs) const
                 -> Vec<aiMesh *>;
      // clang-format on
   };
}
