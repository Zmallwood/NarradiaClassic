#pragma once
#include "../../core-model_structure/model/model.h"
#include "model_part_creator.h"
#include <assimp/scene.h>
#include <map>
#include <memory>
#include <string>
#include <vector>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Creates complete Models out of raw model data.
   ////////////////////////////////////////////////////////////////////////////////
   class ModelCreator : public Singleton<ModelCreator> {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Creates and returns a model interpreted from assimp raw model data.
      ///
      /// @param[in] raw_model Raw model data from assimp.
      /// @return The created model.
      ////////////////////////////////////////////////////////////////////////////////
      auto CreateModel(const aiScene *raw_model) -> std::shared_ptr<Model>;

     private:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets all model parts from raw data of an assimp model.
      ///
      /// @param[in] raw_model Raw model data from assimp.
      /// @return All model parts from the raw model.
      ////////////////////////////////////////////////////////////////////////////////
      auto ModelParts(const aiScene *raw_model);

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Returns a mapping between node names and mesh IDs in an assimp model.
      ///
      /// @param[in] raw_model Raw model data from assimp.
      /// @return A map with key/value-pairs of node-name/mesh-ID.
      ////////////////////////////////////////////////////////////////////////////////
      auto ModelMeshIds(const aiScene *raw_model) const;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Gets all theassimp meshes from a raw assimp model with the provided mesh IDs.
      ///
      /// @param[in] raw_model Raw model data from assimp.
      /// @param[in] node_mesh_ids All mesh IDs for which meshes to contain in the result.
      /// @return All assimp meshes with the provided mesh IDs.
      ////////////////////////////////////////////////////////////////////////////////
      auto NodeMeshes(const aiScene *raw_model, std::vector<int> node_mesh_ids) const;
   };
}
