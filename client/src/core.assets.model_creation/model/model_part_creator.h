#pragma once
#include "../../core.model_structure/model/model_part.h"
#include "../../matter/model/point3f.h"
#include "../../matter/model/color.h"
#include "model_part_keyframe_creator.h"
#include <assimp/scene.h>
#include <map>
#include <memory>
#include <string>
#include <vector>
namespace Narradia
{
   class ModelPartCreator : public Singleton<ModelPartCreator> {
     public:
      auto CreateModelPartFromMesh(const aiScene *scene, std::string node_name, aiMesh *mesh) const
          -> std::shared_ptr<ModelPart>;

     private:
      auto TexNameForMesh(const aiScene *scene, aiMesh *mesh) const;

      auto NewModelPartKeyframe(
          const aiScene *scene, std::string node_name, aiMesh *mesh, aiVectorKey position_keyframe,
          aiQuatKey rotation_keyframe, aiVectorKey scaling_keyframe) const;

      auto TexNames(const aiScene *scene) const;

      auto NodeTransformation(const aiScene *scene, std::string node_name) const;

      auto Position(
          aiVector3D vertex, aiMatrix4x4 node_transformation, aiVectorKey position_keyframe,
          aiQuatKey rotation_keyframe, aiVectorKey scaling_keyframe) const;

      auto Transformations(const aiScene *scene) const;

      auto Translate(Point3F *position, aiVectorKey position_keyframe) const;
   };
}
