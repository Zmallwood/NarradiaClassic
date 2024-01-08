#include "KeyframeCreator.h"

namespace Narradia {
   // Keyframes
   // clang-format off
   auto KeyframeCreator::PosKeyframe(
      const aiScene *_rawModel, 
      String _nodeName, 
      int _keyframeIdx) const -> aiVectorKey {
      // clang-format on
      auto _nodePosKeyframes = NodePosKeyframes(_rawModel, _nodeName);
      aiVectorKey _posKeyframe;
      if (_keyframeIdx < _nodePosKeyframes.size())
         _posKeyframe = _nodePosKeyframes.at(_keyframeIdx);
      else
         _posKeyframe = *(_nodePosKeyframes.end() - 1);
      return _posKeyframe;
   }
   // clang-format off
   auto KeyframeCreator::RotKeyframe(
      const aiScene *_rawModel,
      String _nodeName,
      int _keyframeIdx) const -> aiQuatKey {
      // clang-format on
      auto _nodeRotKeyframes = NodeRotKeyframes(_rawModel, _nodeName);
      aiQuatKey _rotationKeyframe;
      if (_keyframeIdx < _nodeRotKeyframes.size())
         _rotationKeyframe = _nodeRotKeyframes.at(_keyframeIdx);
      else
         _rotationKeyframe = *(_nodeRotKeyframes.end() - 1);
      return _rotationKeyframe;
   }
   // clang-format off
   auto KeyframeCreator::ScalKeyframe(
      const aiScene *_rawModel,
      String _nodeName,
      int _keyframeIdx) const -> aiVectorKey {
      // clang-format on
      auto _nodeScalKeyframes = NodeScalKeyframes(_rawModel, _nodeName);
      aiVectorKey _scalKeyframe;
      if (_keyframeIdx < _nodeScalKeyframes.size())
         _scalKeyframe = _nodeScalKeyframes.at(_keyframeIdx);
      else
         _scalKeyframe = *(_nodeScalKeyframes.end() - 1);
      return _scalKeyframe;
   }
   // Anim keyframes
   auto KeyframeCreator::AnimPosKeyframes(const aiScene *_rawModel) const {
      auto _nodeNameToPosKeyframes = Map<String, Vector<aiVectorKey>>();
      if (_rawModel->mNumAnimations == 0) {
         auto _numMeshes = _rawModel->mNumMeshes;
         for (auto _i = 0; _i < _numMeshes; _i++) {
            auto _mesh = _rawModel->mMeshes[_i];
            auto _origName = String(_mesh->mName.C_Str());
            auto _nodeName = _origName.substr(0, _origName.length() - 5);
            Vector<aiVectorKey> _posKeyframes;
            aiVectorKey _posKeyframe;
            _posKeyframe.mTime = 0.0;
            _posKeyframe.mValue = aiVector3D(0.0, 0.0, 0.0);
            _posKeyframes.push_back(_posKeyframe);
            _nodeNameToPosKeyframes.insert({_nodeName.c_str(), _posKeyframes});
         }
      } else {
         auto _anim0 = _rawModel->mAnimations[0];
         auto _numChannels = _anim0->mNumChannels;
         for (auto _i = 0; _i < _numChannels; _i++) {
            auto _animChannel = _anim0->mChannels[_i];
            auto _nodeName = String(_animChannel->mNodeName.C_Str());
            auto num_position_keys = _animChannel->mNumPositionKeys;
            Vector<aiVectorKey> _posKeyframes;
            aiVectorKey _origPosKeyframe;
            for (auto _j = 0; _j < num_position_keys; _j++) {
               if (_j == 0)
                  _origPosKeyframe = _animChannel->mPositionKeys[_j];
               auto _posKeyframe = _animChannel->mPositionKeys[_j];
               _posKeyframe.mValue -= _origPosKeyframe.mValue;
               _posKeyframe.mValue.z *= -1;
               _posKeyframes.push_back(_posKeyframe);
            }
            if (num_position_keys > 0)
               _nodeNameToPosKeyframes.insert({_nodeName, _posKeyframes});
         }
      }
      return _nodeNameToPosKeyframes;
   }
   auto KeyframeCreator::AnimRotKeyframes(const aiScene *_rawModel) const {
      auto _nodeNameToRotKeyframes = Map<String, Vector<aiQuatKey>>();
      if (_rawModel->mNumAnimations == 0) {
         auto _numMeshes = _rawModel->mNumMeshes;
         for (auto _i = 0; _i < _numMeshes; _i++) {
            auto _mesh = _rawModel->mMeshes[_i];
            auto _origName = String(_mesh->mName.C_Str());
            auto _nodeName = _origName.substr(0, _origName.length() - 5);
            Vector<aiQuatKey> _rotationKeyframes;
            aiQuatKey _rotationKeyframe;
            _rotationKeyframe.mTime = 0.0;
            _rotationKeyframe.mValue = aiQuaternion(0.0, 0.0, 0.0);
            _rotationKeyframes.push_back(_rotationKeyframe);
            _nodeNameToRotKeyframes.insert({_nodeName.c_str(), _rotationKeyframes});
         }
      } else {
         auto _anim0 = _rawModel->mAnimations[0];
         auto _numChannels = _anim0->mNumChannels;
         for (auto _i = 0; _i < _numChannels; _i++) {
            auto _animChannel = _anim0->mChannels[_i];
            auto _nodeName = String(_animChannel->mNodeName.C_Str());
            auto num_rotation_keys = _animChannel->mNumRotationKeys;
            std::vector<aiQuatKey> _rotationKeyframes;
            aiQuatKey _origRotKeyframe;
            for (auto _j = 0; _j < num_rotation_keys; _j++) {
               if (_j == 0)
                  _origRotKeyframe = _animChannel->mRotationKeys[_j];
               auto _rotationKeyframe = _animChannel->mRotationKeys[_j];
               _rotationKeyframe.mValue.x -= _origRotKeyframe.mValue.x;
               _rotationKeyframe.mValue.y -= _origRotKeyframe.mValue.y;
               _rotationKeyframe.mValue.z -= _origRotKeyframe.mValue.z;
               _rotationKeyframes.push_back(_rotationKeyframe);
            }
            if (num_rotation_keys > 0)
               _nodeNameToRotKeyframes.insert({_nodeName, _rotationKeyframes});
         }
      }
      return _nodeNameToRotKeyframes;
   }
   auto KeyframeCreator::AnimScalKeyframes(const aiScene *_rawModel) const {
      auto _nodeNameToScalKeyframes = Map<String, Vector<aiVectorKey>>();
      if (_rawModel->mNumAnimations == 0) {
         auto _numMeshes = _rawModel->mNumMeshes;
         for (auto _i = 0; _i < _numMeshes; _i++) {
            auto _mesh = _rawModel->mMeshes[_i];
            auto _origName = String(_mesh->mName.C_Str());
            auto _nodeName = _origName.substr(0, _origName.length() - 5);
            Vector<aiVectorKey> _scalKeyframes;
            aiVectorKey _scalKeyframe;
            _scalKeyframe.mTime = 0.0;
            _scalKeyframe.mValue = aiVector3D(1.0, -1.0, 1.0);
            _scalKeyframes.push_back(_scalKeyframe);
            _nodeNameToScalKeyframes.insert({_nodeName.c_str(), _scalKeyframes});
         }
      } else {
         auto _anim0 = _rawModel->mAnimations[0];
         auto _numChannels = _anim0->mNumChannels;
         for (auto _i = 0; _i < _numChannels; _i++) {
            auto _animChannel = _anim0->mChannels[_i];
            auto _nodeName = String(_animChannel->mNodeName.C_Str());
            auto _numScalKeys = _animChannel->mNumScalingKeys;
            Vector<aiVectorKey> _scalKeyframes;
            aiVectorKey _origScalKeyframe;
            for (auto _j = 0; _j < _numScalKeys; _j++) {
               if (_j == 0)
                  _origScalKeyframe = _animChannel->mScalingKeys[_i];
               auto _scalKeyframe = _animChannel->mScalingKeys[_j];
               _scalKeyframe.mValue.x /= _origScalKeyframe.mValue.x;
               _scalKeyframe.mValue.y /= _origScalKeyframe.mValue.y;
               _scalKeyframe.mValue.z /= _origScalKeyframe.mValue.z;
               _scalKeyframes.push_back(_scalKeyframe);
            }
            if (_numScalKeys > 0)
               _nodeNameToScalKeyframes.insert({_nodeName, _scalKeyframes});
         }
      }
      return _nodeNameToScalKeyframes;
   }
   // Node keyframes
   auto KeyframeCreator::NodePosKeyframes(const aiScene *_rawModel, String _nodeName) const
       -> Vector<aiVectorKey> {
      auto _allPosKeyframes = AnimPosKeyframes(_rawModel);
      Vector<aiVectorKey> _nodePosKeyframes;
      if (_allPosKeyframes.count(_nodeName))
         _nodePosKeyframes = _allPosKeyframes.at(_nodeName);
      auto _numPosKeyframes = _nodePosKeyframes.size();
      auto _numMaxKeyframes = _numPosKeyframes;
      if (_numMaxKeyframes == 0) {
         _numMaxKeyframes = 1;
         _nodePosKeyframes.push_back(aiVectorKey(0.0, aiVector3D()));
      }
      return _nodePosKeyframes;
   }
   auto KeyframeCreator::NodeRotKeyframes(const aiScene *_rawModel, String _nodeName) const
       -> Vector<aiQuatKey> {
      auto _allRotKeyframes = AnimRotKeyframes(_rawModel);
      Vector<aiQuatKey> _nodeRotKeyframes;
      if (_allRotKeyframes.count(_nodeName))
         _nodeRotKeyframes = _allRotKeyframes.at(_nodeName);
      auto _numRotKeyframes = _nodeRotKeyframes.size();
      auto _numMaxKeyframes = _numRotKeyframes;
      if (_numMaxKeyframes == 0) {
         _numMaxKeyframes = 1;
         _nodeRotKeyframes.push_back(aiQuatKey(0.0, aiQuaternion()));
      }
      return _nodeRotKeyframes;
   }
   auto KeyframeCreator::NodeScalKeyframes(const aiScene *_rawModel, String _nodeName) const
       -> Vector<aiVectorKey> {
      auto _allScalKeyframes = AnimScalKeyframes(_rawModel);
      Vector<aiVectorKey> _nodeScalKeyframes;
      if (_allScalKeyframes.count(_nodeName))
         _nodeScalKeyframes = _allScalKeyframes.at(_nodeName);
      auto _numScalKeyframes = _nodeScalKeyframes.size();
      auto _numMaxKeyframes = _numScalKeyframes;
      if (_numMaxKeyframes == 0) {
         _numMaxKeyframes = 1;
         _nodeScalKeyframes.push_back(aiVectorKey(0.0, aiVector3D(1.0)));
      }
      return _nodeScalKeyframes;
   }
}
