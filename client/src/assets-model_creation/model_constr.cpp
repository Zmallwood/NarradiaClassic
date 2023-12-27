#if 1
#include "model_constr.h"
#include "model_part_constr.h"
#include "assets.h"
#include "mesh_obtainer.h"
#endif

namespace Narradia
{
   auto ModelConstr::ModelParts(const aiScene *raw_model)
   {
      std::vector<std::shared_ptr<ModelPart>> all_model_parts;
      for (auto &entry : MeshObtainer::get()->ModelMeshIds(raw_model))
      {
         std::string node_name = *entry.first;
         auto node_mesh_ids = entry.second;
         for (auto &mesh : MeshObtainer::get()->NodeMeshes(raw_model, node_mesh_ids))
         {
            auto new_model_part =
                ModelPartConstr::get()->CreateModelPartFromMesh(raw_model, node_name, mesh);
            all_model_parts.push_back(new_model_part);
         }
      }
      return all_model_parts;
   }
   auto ModelConstr::CreateModel(const aiScene *raw_model) -> std::shared_ptr<Model>
   {
      auto anim_duration = raw_model->mNumAnimations > 0 ? raw_model->mAnimations[0]->mDuration : 0;
      auto new_model = std::make_shared<Model>(anim_duration);
      for (auto &model_part : ModelParts(raw_model))
         new_model->model_parts()->push_back(model_part);
      return new_model;
   }
}
