#include "nModelPartCreator.h"
#include "nKeyframeCreator.h"
#include "Core/Assets/nModelBank.h"
#include "Core/Assets/ModelStructure/nKeyframe.h"
#include "Core/Assets/ModelStructure/nModelPart.h"

namespace Narradia {
   auto nModelPartCreator::TexNames(const aiScene *_rawModel) const {
      Vec<String> _texNames;
      auto _numMaterials = _rawModel->mNumMaterials;
      for (auto i = 0; i < _numMaterials; i++) {
         aiString _texNameCStr;
         _rawModel->mMaterials[i]->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), _texNameCStr);
         auto _texName = std::string(_texNameCStr.C_Str());
         auto _texName_no_extension = _texName.substr(0, _texName.length() - 4);
         _texNames.push_back(_texName_no_extension);
      }
      return _texNames;
   }

   auto nModelPartCreator::TexNameForMesh(const aiScene *_rawModel, aiMesh *_mesh) const {
      auto _texNames = TexNames(_rawModel);
      auto _material = _mesh->mMaterialIndex;
      auto _texName = _texNames.at(_material);
      return _texName;
   }

   auto nModelPartCreator::Transformations(const aiScene *_rawModel) const {
      auto _rootNode = _rawModel->mRootNode;
      auto _numNodes = _rootNode->mNumChildren;
      auto _nodeName_to_transformations = Map<SharedPtr<String>, aiMatrix4x4>();
      for (auto i = 0; i < _numNodes; i++) {
         auto _node = _rootNode->mChildren[i];
         auto _nodeName = _node->mName;
         auto _nodeTransform = _node->mTransformation;
         _nodeName_to_transformations.insert(
             {MakeShared<String>(_nodeName.C_Str()), _nodeTransform});
      }
      return _nodeName_to_transformations;
   }

   auto nModelPartCreator::NodeTransformation(const aiScene *_rawModel, String _nodeName) const {
      auto _allTransforms = Transformations(_rawModel);
      for (auto &_alpha : _allTransforms) {
         if (*_alpha.first == _nodeName.data())
            return _alpha.second;
      }
      return aiMatrix4x4();
   }

   auto nModelPartCreator::Translate(Point3F *_pos, aiVectorKey _posKeyframe) const {
      auto _translMat = aiMatrix4x4();
      _translMat[0][3] = _posKeyframe.mValue.x;
      _translMat[1][3] = _posKeyframe.mValue.y;
      _translMat[2][3] = _posKeyframe.mValue.z;
      _translMat[0][0] = 1;
      _translMat[1][1] = 1;
      _translMat[2][2] = 1;
      _translMat[3][3] = 1;
      auto _aiPos = aiVector3D{_pos->x, _pos->y, _pos->z};
      _aiPos = _translMat * _aiPos;
      *_pos = {-_aiPos.x, _aiPos.y, _aiPos.z};
   }

   // clang-format off
   auto nModelPartCreator::Position(
      aiVector3D _vertex, 
      aiMatrix4x4 _nodeTransform,
      aiVectorKey _posKeyframe,
      aiQuatKey _rotKeyframe,
      aiVectorKey _scalKeyframe) const {
      // clang-format on
      aiVector3D _aiPos = {_vertex.x, _vertex.y, _vertex.z};
      _aiPos.x *= _scalKeyframe.mValue.x;
      _aiPos.y *= _scalKeyframe.mValue.y;
      _aiPos.z *= _scalKeyframe.mValue.z;
      _aiPos = _rotKeyframe.mValue.GetMatrix() * _aiPos;
      _aiPos = _nodeTransform * _aiPos;
      auto _pos = Point3F{_aiPos.x, _aiPos.y, _aiPos.z};
      Translate(&_pos, _posKeyframe);
      _aiPos = {_pos.x, _pos.y, _pos.z};
      _pos = {_aiPos.x, _aiPos.y, _aiPos.z};
      float _temp;
      _temp = _pos.y;
      _pos.y = _pos.z;
      _pos.z = _temp;
      return _pos;
   }

   // clang-format off
   auto nModelPartCreator::NewModelPartKeyframe(
      const aiScene *_rawModel,
      String _nodeName,
      aiMesh *_mesh,
      aiVectorKey _posKeyframe,
      aiQuatKey _rotKeyframe,
      aiVectorKey _scalKeyframe) const {
      // clang-format on
      auto _newModelPartKeyframe = MakeShared<nKeyframe>();
      auto _nodeTransform = NodeTransformation(_rawModel, _nodeName);
      auto _numVerts = _mesh->mNumVertices;
      for (auto i = 0; i < _numVerts; i++) {
         auto _meshVert = _mesh->mVertices[i];
         auto _meshNormal = _mesh->mNormals[i];
         auto _meshUV = _mesh->mTextureCoords[0][i];
         auto _pos = Position(_meshVert, _nodeTransform, _posKeyframe, _rotKeyframe, _scalKeyframe);
         auto _color = Color{0.0f, 0.0f, 0.0f, 0.0f};
         auto _normal =
             Position(_meshNormal, _nodeTransform, _posKeyframe, _rotKeyframe, _scalKeyframe);
         auto _uv = PointF{1.0f - _meshUV.x, 1.0f - _meshUV.y};
         Vertex3F _animVert;
         _animVert.pos = _pos;
         _animVert.color = _color;
         _animVert.normal = _normal;
         _animVert.uv = _uv;
         _newModelPartKeyframe->vertices.push_back(_animVert);
      }
      return _newModelPartKeyframe;
   }

   // clang-format off
   auto nModelPartCreator::CreateModelPartFromMesh(
      const aiScene *_rawModel,
      String _nodeName,
      aiMesh *_mesh) const -> SharedPtr<nModelPart> {
      // clang-format on
      auto _newModelPart = MakeShared<nModelPart>();
      auto _texName = TexNameForMesh(_rawModel, _mesh);
      _newModelPart->SetTexName(_texName);
      auto _noKeyframeAtTime0Exists =
          nKeyframeCreator::get()->PosKeyframe(_rawModel, _nodeName, 0).mTime > 0;
      auto _numKeyframes = nKeyframeCreator::get()->NodePosKeyframes(_rawModel, _nodeName).size();
      for (auto _k = 0; _k < _numKeyframes; _k++) {
         auto _posKeyframe = nKeyframeCreator::get()->PosKeyframe(_rawModel, _nodeName, _k);
         auto _rotKeyframe = nKeyframeCreator::get()->RotKeyframe(_rawModel, _nodeName, _k);
         auto _scalKeyframe = nKeyframeCreator::get()->ScalKeyframe(_rawModel, _nodeName, _k);
         auto _keyframeTime = static_cast<float>(_posKeyframe.mTime);
         auto _newModelPartKeyframe = NewModelPartKeyframe(
             _rawModel, _nodeName, _mesh, _posKeyframe, _rotKeyframe, _scalKeyframe);
         _newModelPart->Timeline()->keyframes.insert({_keyframeTime, _newModelPartKeyframe});
         if (_noKeyframeAtTime0Exists && _k == 0)
            _newModelPart->Timeline()->keyframes.insert({0.0f, _newModelPartKeyframe});
      }
      return _newModelPart;
   }
}
