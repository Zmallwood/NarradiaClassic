#pragma once

namespace Narradia {
   class KeyframeCreator : public Singleton<KeyframeCreator> {
     public:
      // clang-format off
      auto PosKeyframe(
              const aiScene *_rawModel,
              String _nodeName,
              int _keyframeIdx) const -> aiVectorKey;
      auto RotKeyframe(
              const aiScene *_rawModel,
              String _nodeName,
              int _keyframeIdx) const -> aiQuatKey;
      auto ScalKeyframe(
              const aiScene *_rawModel,
              String _nodeName,
              int _keyframeIdx) const -> aiVectorKey;
      auto NodePosKeyframes(
              const aiScene *_rawModel,
              String _nodeName) const -> Vector<aiVectorKey>;
      auto NodeRotKeyframes(
              const aiScene *_rawModel,
              String _nodeName) const -> Vector<aiQuatKey>;
      auto NodeScalKeyframes(
              const aiScene *_rawModel,
              String _nodeName) const -> Vector<aiVectorKey>;
      // clang-format on

     private:
      auto AnimPosKeyframes(const aiScene *_rawModel) const;
      auto AnimRotKeyframes(const aiScene *_rawModel) const;
      auto AnimScalKeyframes(const aiScene *_rawModel) const;
   };
}
