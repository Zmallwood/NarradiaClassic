#pragma once
namespace Narradia
{
    class Model;
    class ModelPart;

    class ModelCreator : public Singleton<ModelCreator> {
      public:
        auto CreateModel(const aiScene *scene) -> std::shared_ptr<Model>;
      private:
        auto GetModelParts(const aiScene *scene);

        auto GetModelMeshIds(const aiScene *scene) const;

        auto GetNodeMeshes(const aiScene *scene, std::vector<int> node_mesh_ids) const;
    };
}
