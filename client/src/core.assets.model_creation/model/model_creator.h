#pragma once
#include "../../core.model_structure/model/model.h"
#include "model_part_creator.h"
#include <assimp/scene.h>
#include <map>
#include <memory>
#include <string>
#include <vector>
namespace Narradia
{
   class ModelCreator : public Singleton<ModelCreator> {
     public:
      auto CreateModel(const aiScene *scene) -> std::shared_ptr<Model>;

     private:
      auto ModelParts(const aiScene *scene);

      auto ModelMeshIds(const aiScene *scene) const;

      auto NodeMeshes(const aiScene *scene, std::vector<int> node_mesh_ids) const;
   };
}
