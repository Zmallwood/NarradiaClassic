#pragma once
#include "core-model_struct/m/model.h"
#include "model_part_creator.h"
namespace Narradia
{
   class ModelCreator : public Singleton<ModelCreator>
   {
     public:
      auto CreateModel(const aiScene *raw_model) -> std::shared_ptr<Model>;

     private:
      auto ModelParts(const aiScene *raw_model);

      auto ModelMeshIds(const aiScene *raw_model) const;

      auto NodeMeshes(const aiScene *raw_model, std::vector<int> node_mesh_ids) const;
   };
}
