#pragma once

namespace Narradia
{
   class ModelPart;

   class ModelPartConstr : public S<ModelPartConstr>
   {
     public:
      auto
      CreateModelPartFromMesh(const aiScene *raw_model, std::string node_name, aiMesh *mesh) const
          -> std::shared_ptr<ModelPart>;

     private:
      auto TexNameForMesh(const aiScene *raw_model, aiMesh *mesh) const;
      auto NewModelPartKeyframe(
          const aiScene *raw_model, std::string node_name, aiMesh *mesh,
          aiVectorKey position_keyframe, aiQuatKey rotation_keyframe,
          aiVectorKey scaling_keyframe) const;
      auto TexNames(const aiScene *raw_model) const;
      auto NodeTransformation(const aiScene *raw_model, std::string node_name) const;
      auto Position(
          aiVector3D vertex, aiMatrix4x4 node_transformation, aiVectorKey position_keyframe,
          aiQuatKey rotation_keyframe, aiVectorKey scaling_keyframe) const;
      auto Transformations(const aiScene *raw_model) const;
      auto Translate(Point3F *position, aiVectorKey position_keyframe) const;
   };
}
