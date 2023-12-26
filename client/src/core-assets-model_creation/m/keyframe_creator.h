#pragma once
#include <assimp/scene.h>
#include <map>
#include <vector>
namespace Narradia
{
   class KeyframeCreator : public Singleton<KeyframeCreator>
   {
     public:
      auto
      PositionKeyframe(const aiScene *raw_model, std::string node_name, int keyframe_index) const
          -> aiVectorKey;

      auto
      RotationKeyframe(const aiScene *raw_model, std::string node_name, int keyframe_index) const
          -> aiQuatKey;

      auto
      ScalingKeyframe(const aiScene *raw_model, std::string node_name, int keyframe_index) const
          -> aiVectorKey;

      auto NodePositionKeyframes(const aiScene *raw_model, std::string node_name) const
          -> std::vector<aiVectorKey>;

      auto NodeRotationKeyframes(const aiScene *raw_model, std::string node_name) const
          -> std::vector<aiQuatKey>;

      auto NodeScalingKeyframes(const aiScene *raw_model, std::string node_name) const
          -> std::vector<aiVectorKey>;

     private:
      auto AnimPositionKeyframes(const aiScene *raw_model) const;

      auto AnimRotationKeyframes(const aiScene *raw_model) const;

      auto AnimScalingKeyframes(const aiScene *raw_model) const;
   };
}
