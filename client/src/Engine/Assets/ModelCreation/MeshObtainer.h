#pragma once

namespace Narradia {
   class MeshObtainer : public Singleton<MeshObtainer> {
     public:
      // clang-format off
      auto ModelMeshIds(
              const aiScene *_rawModel) const
                 -> Map<SharedPtr<String>, Vector<int>>;
      auto NodeMeshes(
              const aiScene *_rawModel,
              Vector<int> _nodeMeshIDs) const
                 -> Vector<aiMesh *>;
      // clang-format on
   };
}
