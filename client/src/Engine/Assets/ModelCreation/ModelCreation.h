#pragma once

namespace Narradia {

   class KeyframeCreator : public Singleton<KeyframeCreator> {
     public:
      // clang-format off
      auto PosKeyframe(
              const aiScene *raw_model,
              String node_name,
              int keyframe_index) const -> aiVectorKey;
      auto RotKeyframe(
              const aiScene *raw_model,
              String node_name,
              int keyframe_index) const -> aiQuatKey;
      auto ScalKeyframe(
              const aiScene *raw_model,
              String node_name,
              int keyframe_index) const -> aiVectorKey;
      auto NodePosKeyframes(
              const aiScene *raw_model,
              String node_name) const -> Vector<aiVectorKey>;
      auto NodeRotKeyframes(
              const aiScene *raw_model,
              String node_name) const -> Vector<aiQuatKey>;
      auto NodeScalKeyframes(
              const aiScene *raw_model,
              String node_name) const -> Vector<aiVectorKey>;
      // clang-format on

     private:
      auto AnimPosKeyframes(const aiScene *raw_model) const;
      auto AnimRotKeyframes(const aiScene *raw_model) const;
      auto AnimScalKeyframes(const aiScene *raw_model) const;
   };

   class ModelPart;

   class ModelPartCreator : public Singleton<ModelPartCreator> {
     public:
      // clang-format off
      auto
      CreateModelPartFromMesh(
              const aiScene *raw_model,
              String node_name,
              aiMesh *mesh) const -> SharedPtr<ModelPart>;

     private:
      auto TexNameForMesh(
              const aiScene *raw_model,
              aiMesh *mesh) const;
      auto NewModelPartKeyframe(
              const aiScene *raw_model,
              String node_name,
              aiMesh *mesh,
              aiVectorKey position_keyframe,
              aiQuatKey rotation_keyframe,
              aiVectorKey scaling_keyframe) const;
      auto TexNames(
              const aiScene *raw_model) const;
      auto NodeTransformation(
              const aiScene *raw_model,
              String node_name) const;
      auto Position(
              aiVector3D vertex,
              aiMatrix4x4 node_transformation,
              aiVectorKey position_keyframe,
              aiQuatKey rotation_keyframe,
              aiVectorKey scaling_keyframe) const;
      auto Transformations(
              const aiScene *raw_model) const;
      auto Translate(
              Point3F *position,
              aiVectorKey position_keyframe) const;
      // clang-format on
   };

   class MeshObtainer : public Singleton<MeshObtainer> {
     public:
      // clang-format off
      auto ModelMeshIds(
              const aiScene *raw_model) const
                 -> Map<SharedPtr<String>, Vector<int>>;
      auto NodeMeshes(
              const aiScene *raw_model,
              Vector<int> node_mesh_ids) const
                 -> Vector<aiMesh *>;
      // clang-format on
   };

   class Model;

   class ModelCreator : public Singleton<ModelCreator> {
     public:
      auto CreateModel(const aiScene *raw_model) -> SharedPtr<Model>;

     private:
      auto ModelParts(const aiScene *raw_model);
   };

}
