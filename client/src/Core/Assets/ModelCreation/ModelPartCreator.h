#pragma once

namespace Narradia {
   class ModelPart;

   class ModelPartCreator : public Singleton<ModelPartCreator> {
     public:
      // clang-format off
      auto
      CreateModelPartFromMesh(
              const aiScene *_rawModel,
              String _nodeName,
              aiMesh *_mesh) const -> SharedPtr<ModelPart>;

     private:
      auto TexNameForMesh(
              const aiScene *_rawModel,
              aiMesh *_mesh) const;
      auto NewModelPartKeyframe(
              const aiScene *_rawModel,
              String _nodeName,
              aiMesh *_mesh,
              aiVectorKey _posKeyframe,
              aiQuatKey _rotKeyframe,
              aiVectorKey _scalKeyframe) const;
      auto TexNames(
              const aiScene *_rawModel) const;
      auto NodeTransformation(
              const aiScene *_rawModel,
              String _nodeName) const;
      auto Position(
              aiVector3D _vertex,
              aiMatrix4x4 _nodeTransform,
              aiVectorKey _posKeyframe,
              aiQuatKey _rotKeyframe,
              aiVectorKey _scalKeyframe) const;
      auto Transformations(
              const aiScene *_rawModel) const;
      auto Translate(
              Point3F *_pos,
              aiVectorKey _posKeyframe) const;
      // clang-format on
   };
}
