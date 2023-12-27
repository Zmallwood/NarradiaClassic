#pragma once

namespace Narradia
{
   class KeyframeConstr : public Singleton<KeyframeConstr>
   {
     public:
      auto PosKeyframe(const aiScene *raw_model, std::string node_name, int keyframe_index) const
          -> aiVectorKey;

      auto RotKeyframe(const aiScene *raw_model, std::string node_name, int keyframe_index) const
          -> aiQuatKey;

      auto ScalKeyframe(const aiScene *raw_model, std::string node_name, int keyframe_index) const
          -> aiVectorKey;

      auto NodePosKeyframes(const aiScene *raw_model, std::string node_name) const
          -> std::vector<aiVectorKey>;

      auto NodeRotKeyframes(const aiScene *raw_model, std::string node_name) const
          -> std::vector<aiQuatKey>;

      auto NodeScalKeyframes(const aiScene *raw_model, std::string node_name) const
          -> std::vector<aiVectorKey>;

     private:
      auto AnimPosKeyframes(const aiScene *raw_model) const;

      auto AnimRotKeyframes(const aiScene *raw_model) const;

      auto AnimScalKeyframes(const aiScene *raw_model) const;
   };
}
