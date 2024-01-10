#pragma once

namespace Narradia {
   class nKeyframeCreator : public Singleton<nKeyframeCreator> {
     public:
      // clang-format off
      auto PosKeyframe(
              const aiScene *_rawModel,
              String _nodeName,
              int _kframeIdx) const -> aiVectorKey;
      auto RotKeyframe(
              const aiScene *_rawModel,
              String _nodeName,
              int _kframeIdx) const -> aiQuatKey;
      auto ScalKeyframe(
              const aiScene *_rawModel,
              String _nodeName,
              int _kframeIdx) const -> aiVectorKey;
      auto NodePosKeyframes(
              const aiScene *_rawModel,
              String _nodeName) const -> Vec<aiVectorKey>;
      auto NodeRotKeyframes(
              const aiScene *_rawModel,
              String _nodeName) const -> Vec<aiQuatKey>;
      auto NodeScalKeyframes(
              const aiScene *_rawModel,
              String _nodeName) const -> Vec<aiVectorKey>;
      // clang-format on

     private:
      auto AnimPosKeyframes(const aiScene *_rawModel) const;
      auto AnimRotKeyframes(const aiScene *_rawModel) const;
      auto AnimScalKeyframes(const aiScene *_rawModel) const;
   };
}
