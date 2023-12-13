#include "model_creator.h"
namespace Narradia
{
   std::map<std::shared_ptr<std::string>, std::vector<int>> node_name_to_meshes;

   auto ModelCreator::ModelMeshIds(const aiScene *raw_model) const {
      node_name_to_meshes.clear();
      auto root_node = raw_model->mRootNode;
      auto num_sub_nodes = root_node->mNumChildren;
      for (auto i = 0; i < num_sub_nodes; i++) {
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

   auto ModelCreator::NodeMeshes(const aiScene *raw_model, std::vector<int> node_mesh_ids) const {
      std::vector<aiMesh *> node_meshes;
      auto num_meshes = node_mesh_ids.size();
      for (auto i = 0; i < num_meshes; i++) {
         auto mesh = raw_model->mMeshes[node_mesh_ids.at(i)];
         node_meshes.push_back(mesh);
      }
      return node_meshes;
   }

   auto ModelCreator::ModelParts(const aiScene *raw_model) {
      std::vector<std::shared_ptr<ModelPart>> all_model_parts;
      for (auto &entry : ModelMeshIds(raw_model)) {
         std::string node_name = *entry.first;
         auto node_mesh_ids = entry.second;
         for (auto &mesh : NodeMeshes(raw_model, node_mesh_ids)) {
            auto new_model_part =
                ModelPartCreator::get()->CreateModelPartFromMesh(raw_model, node_name, mesh);
            all_model_parts.push_back(new_model_part);
         }
      }
      return all_model_parts;
   }

   auto ModelCreator::CreateModel(const aiScene *raw_model) -> std::shared_ptr<Model> {
      auto anim_duration = raw_model->mNumAnimations > 0 ? raw_model->mAnimations[0]->mDuration : 0;
      auto new_model = std::make_shared<Model>(anim_duration);
      for (auto &model_part : ModelParts(raw_model))
         new_model->model_parts()->push_back(model_part);
      return new_model;
   }
}
