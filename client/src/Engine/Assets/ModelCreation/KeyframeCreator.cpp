#include "KeyframeCreator.h"

namespace Narradia {
   // Keyframes
   // clang-format off
   auto KeyframeCreator::PosKeyframe(
      const aiScene *_rawModel, 
      String _nodeName, 
      int _kframeIdx) const -> aiVectorKey {
      // clang-format on
      auto _nodePosKframes = NodePosKeyframes(_rawModel, _nodeName);
      aiVectorKey _posKframe;
      if (_kframeIdx < _nodePosKframes.size())
         _posKframe = _nodePosKframes.at(_kframeIdx);
      else
         _posKframe = *(_nodePosKframes.end() - 1);
      return _posKframe;
   }
   // clang-format off
   auto KeyframeCreator::RotKeyframe(
      const aiScene *_rawModel,
      String _nodeName,
      int _kframeIdx) const -> aiQuatKey {
      // clang-format on
      auto _nodeRotKframes = NodeRotKeyframes(_rawModel, _nodeName);
      aiQuatKey _rotKframe;
      if (_kframeIdx < _nodeRotKframes.size())
         _rotKframe = _nodeRotKframes.at(_kframeIdx);
      else
         _rotKframe = *(_nodeRotKframes.end() - 1);
      return _rotKframe;
   }
   // clang-format off
   auto KeyframeCreator::ScalKeyframe(
      const aiScene *_rawModel,
      String _nodeName,
      int _kframeIdx) const -> aiVectorKey {
      // clang-format on
      auto _nodeScalKframes = NodeScalKeyframes(_rawModel, _nodeName);
      aiVectorKey _scalKframe;
      if (_kframeIdx < _nodeScalKframes.size())
         _scalKframe = _nodeScalKframes.at(_kframeIdx);
      else
         _scalKframe = *(_nodeScalKframes.end() - 1);
      return _scalKframe;
   }
   // Anim keyframes
   auto KeyframeCreator::AnimPosKeyframes(const aiScene *_rawModel) const {
      auto _nodeNameToPosKframes = Map<String, Vector<aiVectorKey>>();
      if (_rawModel->mNumAnimations == 0) {
         auto _numMeshes = _rawModel->mNumMeshes;
         for (auto _i = 0; _i < _numMeshes; _i++) {
            auto _mesh = _rawModel->mMeshes[_i];
            auto _origName = String(_mesh->mName.C_Str());
            auto _nodeName = _origName.substr(0, _origName.length() - 5);
            Vector<aiVectorKey> _posKframes;
            aiVectorKey _posKframe;
            _posKframe.mTime = 0.0;
            _posKframe.mValue = aiVector3D(0.0, 0.0, 0.0);
            _posKframes.push_back(_posKframe);
            _nodeNameToPosKframes.insert({_nodeName.c_str(), _posKframes});
         }
      } else {
         auto _anim0 = _rawModel->mAnimations[0];
         auto _numChannels = _anim0->mNumChannels;
         for (auto _i = 0; _i < _numChannels; _i++) {
            auto _animChannel = _anim0->mChannels[_i];
            auto _nodeName = String(_animChannel->mNodeName.C_Str());
            auto num_position_keys = _animChannel->mNumPositionKeys;
            Vector<aiVectorKey> _posKframes;
            aiVectorKey _origPosKeyframe;
            for (auto _j = 0; _j < num_position_keys; _j++) {
               if (_j == 0)
                  _origPosKeyframe = _animChannel->mPositionKeys[_j];
               auto _posKframe = _animChannel->mPositionKeys[_j];
               _posKframe.mValue -= _origPosKeyframe.mValue;
               _posKframe.mValue.z *= -1;
               _posKframes.push_back(_posKframe);
            }
            if (num_position_keys > 0)
               _nodeNameToPosKframes.insert({_nodeName, _posKframes});
         }
      }
      return _nodeNameToPosKframes;
   }
   auto KeyframeCreator::AnimRotKeyframes(const aiScene *_rawModel) const {
      auto _nodeNameToRotKframes = Map<String, Vector<aiQuatKey>>();
      if (_rawModel->mNumAnimations == 0) {
         auto _numMeshes = _rawModel->mNumMeshes;
         for (auto _i = 0; _i < _numMeshes; _i++) {
            auto _mesh = _rawModel->mMeshes[_i];
            auto _origName = String(_mesh->mName.C_Str());
            auto _nodeName = _origName.substr(0, _origName.length() - 5);
            Vector<aiQuatKey> _rotKframes;
            aiQuatKey _rotKframe;
            _rotKframe.mTime = 0.0;
            _rotKframe.mValue = aiQuaternion(0.0, 0.0, 0.0);
            _rotKframes.push_back(_rotKframe);
            _nodeNameToRotKframes.insert({_nodeName.c_str(), _rotKframes});
         }
      } else {
         auto _anim0 = _rawModel->mAnimations[0];
         auto _numChannels = _anim0->mNumChannels;
         for (auto _i = 0; _i < _numChannels; _i++) {
            auto _animChannel = _anim0->mChannels[_i];
            auto _nodeName = String(_animChannel->mNodeName.C_Str());
            auto num_rotation_keys = _animChannel->mNumRotationKeys;
            std::vector<aiQuatKey> _rotKframes;
            aiQuatKey _origRotKeyframe;
            for (auto _j = 0; _j < num_rotation_keys; _j++) {
               if (_j == 0)
                  _origRotKeyframe = _animChannel->mRotationKeys[_j];
               auto _rotKframe = _animChannel->mRotationKeys[_j];
               _rotKframe.mValue.x -= _origRotKeyframe.mValue.x;
               _rotKframe.mValue.y -= _origRotKeyframe.mValue.y;
               _rotKframe.mValue.z -= _origRotKeyframe.mValue.z;
               _rotKframes.push_back(_rotKframe);
            }
            if (num_rotation_keys > 0)
               _nodeNameToRotKframes.insert({_nodeName, _rotKframes});
         }
      }
      return _nodeNameToRotKframes;
   }
   auto KeyframeCreator::AnimScalKeyframes(const aiScene *_rawModel) const {
      auto _nodeNameToScalKframes = Map<String, Vector<aiVectorKey>>();
      if (_rawModel->mNumAnimations == 0) {
         auto _numMeshes = _rawModel->mNumMeshes;
         for (auto _i = 0; _i < _numMeshes; _i++) {
            auto _mesh = _rawModel->mMeshes[_i];
            auto _origName = String(_mesh->mName.C_Str());
            auto _nodeName = _origName.substr(0, _origName.length() - 5);
            Vector<aiVectorKey> _scalKframes;
            aiVectorKey _scalKframe;
            _scalKframe.mTime = 0.0;
            _scalKframe.mValue = aiVector3D(1.0, -1.0, 1.0);
            _scalKframes.push_back(_scalKframe);
            _nodeNameToScalKframes.insert({_nodeName.c_str(), _scalKframes});
         }
      } else {
         auto _anim0 = _rawModel->mAnimations[0];
         auto _numChannels = _anim0->mNumChannels;
         for (auto _i = 0; _i < _numChannels; _i++) {
            auto _animChannel = _anim0->mChannels[_i];
            auto _nodeName = String(_animChannel->mNodeName.C_Str());
            auto _numScalKeys = _animChannel->mNumScalingKeys;
            Vector<aiVectorKey> _scalKframes;
            aiVectorKey _origScalKeyframe;
            for (auto _j = 0; _j < _numScalKeys; _j++) {
               if (_j == 0)
                  _origScalKeyframe = _animChannel->mScalingKeys[_i];
               auto _scalKframe = _animChannel->mScalingKeys[_j];
               _scalKframe.mValue.x /= _origScalKeyframe.mValue.x;
               _scalKframe.mValue.y /= _origScalKeyframe.mValue.y;
               _scalKframe.mValue.z /= _origScalKeyframe.mValue.z;
               _scalKframes.push_back(_scalKframe);
            }
            if (_numScalKeys > 0)
               _nodeNameToScalKframes.insert({_nodeName, _scalKframes});
         }
      }
      return _nodeNameToScalKframes;
   }
   // Node keyframes
   auto KeyframeCreator::NodePosKeyframes(const aiScene *_rawModel, String _nodeName) const
       -> Vector<aiVectorKey> {
      auto _allPosKframes = AnimPosKeyframes(_rawModel);
      Vector<aiVectorKey> _nodePosKframes;
      if (_allPosKframes.count(_nodeName))
         _nodePosKframes = _allPosKframes.at(_nodeName);
      auto _numPosKframes = _nodePosKframes.size();
      auto _numMaxKframes = _numPosKframes;
      if (_numMaxKframes == 0) {
         _numMaxKframes = 1;
         _nodePosKframes.push_back(aiVectorKey(0.0, aiVector3D()));
      }
      return _nodePosKframes;
   }
   auto KeyframeCreator::NodeRotKeyframes(const aiScene *_rawModel, String _nodeName) const
       -> Vector<aiQuatKey> {
      auto _allRotKframes = AnimRotKeyframes(_rawModel);
      Vector<aiQuatKey> _nodeRotKframes;
      if (_allRotKframes.count(_nodeName))
         _nodeRotKframes = _allRotKframes.at(_nodeName);
      auto _numRotKframes = _nodeRotKframes.size();
      auto _numMaxKframes = _numRotKframes;
      if (_numMaxKframes == 0) {
         _numMaxKframes = 1;
         _nodeRotKframes.push_back(aiQuatKey(0.0, aiQuaternion()));
      }
      return _nodeRotKframes;
   }
   auto KeyframeCreator::NodeScalKeyframes(const aiScene *_rawModel, String _nodeName) const
       -> Vector<aiVectorKey> {
      auto _allScalKframes = AnimScalKeyframes(_rawModel);
      Vector<aiVectorKey> _nodeScalKframes;
      if (_allScalKframes.count(_nodeName))
         _nodeScalKframes = _allScalKframes.at(_nodeName);
      auto _numScalKframes = _nodeScalKframes.size();
      auto _numMaxKframes = _numScalKframes;
      if (_numMaxKframes == 0) {
         _numMaxKframes = 1;
         _nodeScalKframes.push_back(aiVectorKey(0.0, aiVector3D(1.0)));
      }
      return _nodeScalKframes;
   }
}
