#pragma once
#include "../../core-model_struct/m/model_part.h"
#include "../../matter/m/color.h"
#include "../../matter/m/point3f.h"
#include "keyframe_creator.h"
#include <assimp/scene.h>
#include <map>
#include <memory>
#include <string>
#include <vector>
namespace Narradia
{
   class ModelPartCreator : public Singleton<ModelPartCreator>
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
