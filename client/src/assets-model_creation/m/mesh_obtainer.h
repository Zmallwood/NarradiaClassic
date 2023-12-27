#pragma once

namespace Narradia
{
   class MeshObtainer : public Singleton<MeshObtainer>
   {
     public:
      auto ModelMeshIds(const aiScene *raw_model) const
          -> std::map<std::shared_ptr<std::string>, std::vector<int>>;

      auto NodeMeshes(const aiScene *raw_model, std::vector<int> node_mesh_ids) const
          -> std::vector<aiMesh *>;
   };
}
