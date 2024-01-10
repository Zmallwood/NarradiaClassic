#include "ModelsRendering.h"
#include "Core/Assets/ModelStructure/nModel.h"
#include "Core/Assets/nImageBank.h"
#include "Core/Assets/nModelBank.h"
#include "Math/Calc.h"
#include "RenderingCore.h"
#include "WorldStructure/Actors/Player.h"
#include "WorldStructure/WorldStructure.h"
#include "nRendModelsView.h"

namespace Narradia {
   void NewModel(StringView _modelName) {
      auto _rend = nRendModelsView::get();
      auto _model = nModelBank::get()->GetModel(_modelName);
      auto _modelIDs = _rend->model_ids();
      _modelIDs->insert({_modelName.data(), Map<int, Map<float, const nBodyData>>()});
      auto _iBody = 0;
      for (auto &_body : *_model->ModelParts()) {
         auto &_timelines = _body->Timeline()->keyframes;
         for (auto &_keyframe : _timelines) {
            auto _keyframeTime = _keyframe.first;
            auto _animKeyBodyKeyframe = _keyframe.second;
            auto _vertexCount = _animKeyBodyKeyframe->vertices.size();
            auto _bodyKeyframe_id =
                nRendModelsView::get()->NewBodyKeyframe(_modelName, _keyframeTime);
            if (_modelIDs->at(_modelName.data()).count(_iBody) == 0)
               _modelIDs->at(_modelName.data()).insert({_iBody, Map<float, const nBodyData>()});
            nBodyData _bodyData;
            _bodyData.RID= _bodyKeyframe_id;
            _bodyData.imgName = _body->TexName();
            _bodyData.numVertices = _vertexCount;
            _modelIDs->at(_modelName.data()).at(_iBody).insert({_keyframeTime, _bodyData});
            auto &_model_keyframe = _body->Timeline()->keyframes.at(_keyframeTime);
            Vec<Vertex3F> _vertices;
            Vec<Point3F> _normals;
            auto &_animVertices = _model_keyframe->vertices;
            for (auto _v : _animVertices) {
               Vertex3F _v3f;
               _v3f.pos = _v.pos;
               _v3f.color = _v.color;
               _v3f.uv = _v.uv;
               _vertices.push_back(_v3f);
               Point3F _n3f;
               _n3f.x = _v.normal.x;
               _n3f.y = _v.normal.y;
               _n3f.z = _v.normal.z;
               _normals.push_back(_n3f);
            }
            nRendModelsView::get()->NewBodyKeyframeGeometry(_bodyKeyframe_id, _vertices, _normals);
         }
         _iBody++;
      }
   }

   // clang-format off
   void DrawModel(
       StringView _modelName, 
       float _msTime, 
       Point3F _position, 
       float _rotation, 
       float _scaling,
       float _brightness, 
       glm::vec3 _colorMod, 
       bool _noFog, 
       bool _noLighting) {
      // clang-format on
      auto _rend = nRendModelsView::get();
      auto _modelIDs = _rend->model_ids();
      auto _isBatchDrawing = _rend->is_batch_drawing();
      if (_modelIDs->count(_modelName.data()) == 0)
         return;
      if (!_isBatchDrawing) {
         glEnable(GL_DEPTH_TEST);
         glUseProgram(_rend->shader_program_view()->shader_program()->program_id());
         glUniformMatrix4fv(
             _rend->location_projection(), 1, GL_FALSE,
             value_ptr(CameraGL::get()->persp_matrix()));
         glUniformMatrix4fv(
             _rend->location_view(), 1, GL_FALSE,
             glm::value_ptr(CameraGL::get()->view_matrix()));
      }
      auto _model_matrix = glm::rotate(
          glm::scale(
              glm::translate(glm::mat4(1.0), glm::vec3(_position.x, _position.y, _position.z)),
              glm::vec3(_scaling, _scaling, _scaling)),
          glm::radians(_rotation), glm::vec3(0, 1, 0));
      auto _model_no_translation_matrix = glm::rotate(
          glm::scale(
              glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0)),
              glm::vec3(_scaling, _scaling, _scaling)),
          glm::radians(_rotation), glm::vec3(0, 1, 0));
      glUniformMatrix4fv(_rend->location_model(), 1, GL_FALSE, glm::value_ptr(_model_matrix));
      glUniformMatrix4fv(
          _rend->location_model_no_translation(), 1, GL_FALSE,
          glm::value_ptr(_model_no_translation_matrix));
      glUniform3fv(_rend->location_color_mod(), 1, glm::value_ptr(_colorMod));
      auto _playerSpaceCoord = Player::get()->pos().Multiply(k_tileSize);
      auto _currWorldLoc = Player::get()->world_location();
      auto _currWorldArea = World::get()->CurrWorldArea();
      auto _tileSize = k_tileSize;
      auto _mapOffsX = _currWorldLoc.x * _currWorldArea->Width() * _tileSize;
      auto _mapOffsY = _currWorldLoc.y * _currWorldArea->Height() * _tileSize;
      _playerSpaceCoord.x += _mapOffsX;
      _playerSpaceCoord.z += _mapOffsY;
      glm::vec3 _viewPos(
          _playerSpaceCoord.x,
          _playerSpaceCoord.y +
              CalcTileAverageElevation(
                  Player::get()->pos().GetXZ().ToIntPoint(), Player::get()->world_location()),
          _playerSpaceCoord.z);
      glUniform3fv(_rend->location_view_pos(), 1, glm::value_ptr(_viewPos));
      glm::vec3 _fogColorGL(
          nRendModelsView::get()->fog_color_models().r,
          nRendModelsView::get()->fog_color_models().g,
          nRendModelsView::get()->fog_color_models().b);
      glUniform3fv(_rend->location_fog_color(), 1, glm::value_ptr(_fogColorGL));
      glUniform1f(_rend->location_alpha(), _brightness);
      glUniform1f(_rend->location_no_fog(), _noFog ? 1.0f : 0.0f);
      glUniform1f(_rend->location_no_lighting(), _noLighting ? 1.0f : 0.0f);
      auto &_allNodes = _modelIDs->at(_modelName.data());
      auto _pModel = nModelBank::get()->GetModel(_modelName);
      int _msTime_used;
      if (_pModel->AnimDuration() == 0)
         _msTime_used = 0;
      else
         _msTime_used = static_cast<int>(_msTime * _rend->global_animation_speed()) %
                        _pModel->AnimDuration();
      auto &_model_data = _allNodes;
      for (auto &_entry : _allNodes) {
         auto &_timeline = _entry.second;
         auto _foundTime = -1.0f;
         const nBodyData *_pBodyData = nullptr;

         for (auto &_keyframe : _timeline) {
            auto _time = _keyframe.first;
            if (_msTime_used >= _time)
               _foundTime = _time;
         }
         auto &_bodyData = _timeline.at(_foundTime);
         glBindVertexArray(_bodyData.RID);
         auto _imgID = nImageBank::get()->GetImage(_bodyData.imgName);
         glBindTexture(GL_TEXTURE_2D, _imgID);
         glDrawElements(GL_TRIANGLES, _bodyData.numVertices, GL_UNSIGNED_INT, NULL);
      }
      glBindVertexArray(0);
      if (!_isBatchDrawing)
         glUseProgram(0);
   }

   void StartModelsBatchDrawing() {
      auto _rend = nRendModelsView::get();
      _rend->set_is_batch_drawing(true);
      glEnable(GL_DEPTH_TEST);
      glUseProgram(_rend->shader_program_view()->shader_program()->program_id());
      glUniformMatrix4fv(
          _rend->location_projection(), 1, GL_FALSE, value_ptr(CameraGL::get()->persp_matrix()));
      glUniformMatrix4fv(
          _rend->location_view(), 1, GL_FALSE, glm::value_ptr(CameraGL::get()->view_matrix()));
   }

   void StopModelsBatchDrawing() {
      auto _rend = nRendModelsView::get();
      _rend->set_is_batch_drawing(false);
   }
}
