#include "mesh_obtainer.h"

namespace Narradia
{
   auto MeshObtainer::ModelMeshIds(const aiScene *raw_model) const
       -> std::map<std::shared_ptr<std::string>, std::vector<int>>
   {
      std::map<std::shared_ptr<std::string>, std::vector<int>> node_name_to_meshes;
      auto root_node = raw_model->mRootNode;
      auto num_sub_nodes = root_node->mNumChildren;
      for (auto i = 0; i < num_sub_nodes; i++)
      {
         auto sub_node = root_node->mChildren[i];
         auto sub_node_name = sub_node->mName;
         auto num_meshes = sub_node->mNumMeshes;
         std::vector<int> meshes;
         for (auto j = 0; j < num_meshes; j++)
            meshes.push_back(sub_node->mMeshes[j]);
         const char *c_str = sub_node_name.C_Str();
         auto key = std::string{c_str};
         node_name_to_meshes.insert({std::make_shared<std::string>(key), meshes});
      }
      return node_name_to_meshes;
   }
   auto MeshObtainer::NodeMeshes(const aiScene *raw_model, std::vector<int> node_mesh_ids) const
       -> std::vector<aiMesh *>
   {
      std::vector<aiMesh *> node_meshes;
      auto num_meshes = node_mesh_ids.size();
      for (auto i = 0; i < num_meshes; i++)
      {
         auto mesh = raw_model->mMeshes[node_mesh_ids.at(i)];
         node_meshes.push_back(mesh);
      }
      return node_meshes;
   }
}
