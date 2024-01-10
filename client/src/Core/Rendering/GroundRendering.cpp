#include "GroundRendering.h"
#include "Core/Assets/nImageBank.h"
#include "Core/Assets/nModelBank.h"
#include "Math/Calc.h"
#include "RendColorsView.h"
#include "RendGroundView.h"
#include "WorldStructure/Actors/Player.h"
#include "WorldStructure/WorldStructure.h"

namespace Narradia {
   RenderID NewTile() {
      auto _numVerts = 4;
      auto _rend = RendGroundView::get();
      auto _rendBase = _rend->renderer_base();
      auto _VAOID = _rendBase->GenNewVAOId();
      auto _indexBufID = _rendBase->GenNewBufId(BufferTypes::Indices, _VAOID);
      auto _posBufID = _rendBase->GenNewBufId(BufferTypes::Positions3D, _VAOID);
      auto _colorBufID = _rendBase->GenNewBufId(BufferTypes::Colors, _VAOID);
      auto _uvBufID = _rendBase->GenNewBufId(BufferTypes::Uvs, _VAOID);
      auto _normBufID = _rendBase->GenNewBufId(BufferTypes::Normals, _VAOID);
      glBindVertexArray(_VAOID);
      _rend->SetIndicesData(_indexBufID, _numVerts, nullptr);
      _rend->SetData(_posBufID, _numVerts, nullptr, BufferTypes::Positions3D);
      _rend->SetData(_colorBufID, _numVerts, nullptr, BufferTypes::Colors);
      _rend->SetData(_uvBufID, _numVerts, nullptr, BufferTypes::Uvs);
      _rend->SetData(_normBufID, _numVerts, nullptr, BufferTypes::Normals);
      glBindVertexArray(0);
      return _VAOID;
   }

   RenderID NewTileSurface() {
      auto _numVerts = 6 * 100 * 100;
      auto _rend = RendGroundView::get();
      auto _rendBase = _rend->renderer_base();
      auto _VAOID = _rendBase->GenNewVAOId();
      auto _indexBufID = _rendBase->GenNewBufId(BufferTypes::Indices, _VAOID);
      auto _posBufID = _rendBase->GenNewBufId(BufferTypes::Positions3D, _VAOID);
      auto _colorBufID = _rendBase->GenNewBufId(BufferTypes::Colors, _VAOID);
      auto _uvBufID = _rendBase->GenNewBufId(BufferTypes::Uvs, _VAOID);
      auto _normBufID = _rendBase->GenNewBufId(BufferTypes::Normals, _VAOID);
      glBindVertexArray(_VAOID);
      _rend->SetIndicesData(_indexBufID, _numVerts, nullptr);
      _rend->SetData(_posBufID, _numVerts, nullptr, BufferTypes::Positions3D);
      _rend->SetData(_colorBufID, _numVerts, nullptr, BufferTypes::Colors);
      _rend->SetData(_uvBufID, _numVerts, nullptr, BufferTypes::Uvs);
      _rend->SetData(_normBufID, _numVerts, nullptr, BufferTypes::Normals);
      glBindVertexArray(0);
      return _VAOID;
   }

   void SetTileSufaceGeom(RenderID _VAOID, Vec<Vec<Square<Vertex3F>>> &_verts) {
      Vec<Vertex3F> _vertsVec;
      for (auto _y = 0; _y < 100; _y++) {
         for (auto _x = 0; _x < 100; _x++) {
            auto _entry = _verts.at(_x).at(_y);
            _vertsVec.push_back(_entry._00);
            _vertsVec.push_back(_entry._10);
            _vertsVec.push_back(_entry._11);
            _vertsVec.push_back(_entry._00);
            _vertsVec.push_back(_entry._11);
            _vertsVec.push_back(_entry._01);
         }
      }
      auto _rend = RendGroundView::get();
      auto _rendBase = _rend->renderer_base();
      if (!_rend->is_batch_drawing())
         _rend->UseVAOBegin(_VAOID);
      Vec<int> _indices(_vertsVec.size());
      std::iota(std::begin(_indices), std::end(_indices), 0);
      Vec<float> _positions;
      Vec<float> _colors;
      Vec<float> _uvs;
      Vec<float> _normals;
      for (auto &_vert : _vertsVec) {
         _positions.push_back(_vert.pos.x);
         _positions.push_back(_vert.pos.y);
         _positions.push_back(_vert.pos.z);
         _colors.push_back(_vert.color.r);
         _colors.push_back(_vert.color.g);
         _colors.push_back(_vert.color.b);
         _colors.push_back(_vert.color.a);
         _uvs.push_back(_vert.uv.x);
         _uvs.push_back(_vert.uv.y);
         auto _vert_normal = _vert.normal;
         _normals.push_back(_vert_normal.x);
         _normals.push_back(_vert_normal.y);
         _normals.push_back(_vert_normal.z);
      }
      auto _indexBufID = _rendBase->BufId(BufferTypes::Indices, _VAOID);
      auto _posBufID = _rendBase->BufId(BufferTypes::Positions3D, _VAOID);
      auto _colorBufID = _rendBase->BufId(BufferTypes::Colors, _VAOID);
      auto _uvBufID = _rendBase->BufId(BufferTypes::Uvs, _VAOID);
      auto _normBufID = _rendBase->BufId(BufferTypes::Normals, _VAOID);
      glBindVertexArray(_VAOID);
      _rend->UpdateIndicesData(_indexBufID, _indices);
      _rend->UpdateData(
          _posBufID, _positions, BufferTypes::Positions3D, RendGroundView::kLocationPosition);
      _rend->UpdateData(_colorBufID, _colors, BufferTypes::Colors, RendGroundView::kLocationColor);
      _rend->UpdateData(_uvBufID, _uvs, BufferTypes::Uvs, RendGroundView::kLocationUv);
      _rend->UpdateData(
          _normBufID, _normals, BufferTypes::Normals, RendGroundView::kLocationNormal);
      glBindVertexArray(0);
      if (!_rend->is_batch_drawing())
         _rend->UseVAOEnd();
   }

   void SetTileGeom(RenderID _VAOID, Square<Vertex3F> &_verts) {
      Vec<Vertex3F> _vertsVec;
      _vertsVec.push_back(_verts._00);
      _vertsVec.push_back(_verts._10);
      _vertsVec.push_back(_verts._11);
      _vertsVec.push_back(_verts._01);
      auto _rend = RendGroundView::get();
      auto _rendBase = _rend->renderer_base();
      if (!_rend->is_batch_drawing())
         _rend->UseVAOBegin(_VAOID);
      Vec<int> _indices(_vertsVec.size());
      std::iota(std::begin(_indices), std::end(_indices), 0);
      Vec<float> _positions;
      Vec<float> _colors;
      Vec<float> _uvs;
      Vec<float> _normals;
      for (auto &_vert : _vertsVec) {
         _positions.push_back(_vert.pos.x);
         _positions.push_back(_vert.pos.y);
         _positions.push_back(_vert.pos.z);
         _colors.push_back(_vert.color.r);
         _colors.push_back(_vert.color.g);
         _colors.push_back(_vert.color.b);
         _colors.push_back(_vert.color.a);
         _uvs.push_back(_vert.uv.x);
         _uvs.push_back(_vert.uv.y);
         auto _vert_normal = _vert.normal;
         _normals.push_back(_vert_normal.x);
         _normals.push_back(_vert_normal.y);
         _normals.push_back(_vert_normal.z);
      }
      auto _indexBufID = _rendBase->BufId(BufferTypes::Indices, _VAOID);
      auto _posBufID = _rendBase->BufId(BufferTypes::Positions3D, _VAOID);
      auto _colorBufID = _rendBase->BufId(BufferTypes::Colors, _VAOID);
      auto _uvBufID = _rendBase->BufId(BufferTypes::Uvs, _VAOID);
      auto _normBufID = _rendBase->BufId(BufferTypes::Normals, _VAOID);
      glBindVertexArray(_VAOID);
      _rend->UpdateIndicesData(_indexBufID, _indices);
      _rend->UpdateData(
          _posBufID, _positions, BufferTypes::Positions3D, RendGroundView::kLocationPosition);
      _rend->UpdateData(_colorBufID, _colors, BufferTypes::Colors, RendGroundView::kLocationColor);
      _rend->UpdateData(_uvBufID, _uvs, BufferTypes::Uvs, RendGroundView::kLocationUv);
      _rend->UpdateData(
          _normBufID, _normals, BufferTypes::Normals, RendGroundView::kLocationNormal);
      glBindVertexArray(0);
      if (!_rend->is_batch_drawing())
         _rend->UseVAOEnd();
   }

   void DrawTileSurface(StringView _imgName, RenderID _VAOID, bool _depthTestOff) {
      auto _vert_count = 6 * 100 * 100;
      auto _rend = RendGroundView::get();
      if (_depthTestOff)
         glDisable(GL_DEPTH_TEST);
      else
         glEnable(GL_DEPTH_TEST);
      _rend->UseVAOBegin(_VAOID);
      glUseProgram(_rend->shader_program_view()->shader_program()->program_id());
      glUniformMatrix4fv(
          _rend->location_projection(), 1, GL_FALSE,
          glm::value_ptr(CameraGL::get()->persp_matrix()));
      glUniformMatrix4fv(
          _rend->location_view(), 1, GL_FALSE, glm::value_ptr(CameraGL::get()->view_matrix()));
      glm::mat4 _model(1.0);
      glUniformMatrix4fv(_rend->location_model(), 1, GL_FALSE, glm::value_ptr(_model));
      glUniform1f(_rend->location_alpha(), 1.0f);
      auto _playerPos = Player::get()->pos().Multiply(k_tileSize);
      auto _currMapLoc = Player::get()->world_location();
      auto _worldArea = World::get()->CurrWorldArea();
      auto _tileSize = k_tileSize;
      auto _mapOffsX = _currMapLoc.x * _worldArea->Width() * _tileSize;
      auto _mapOffsY = _currMapLoc.y * _worldArea->Height() * _tileSize;
      _playerPos.x += _mapOffsX;
      _playerPos.z += _mapOffsY;
      glm::vec3 _viewPos(
          _playerPos.x,
          _playerPos.y +
              CalcTileAverageElevation(
                  Player::get()->pos().GetXZ().ToIntPoint(), Player::get()->world_location()),
          _playerPos.z);
      glUniform3fv(_rend->location_view_pos(), 1, glm::value_ptr(_viewPos));
      glm::vec3 _fogColorGL(
          RendGroundView::get()->fog_color_ground().r, RendGroundView::get()->fog_color_ground().g,
          RendGroundView::get()->fog_color_ground().b);
      glUniform3fv(_rend->location_fog_color(), 1, glm::value_ptr(_fogColorGL));
      glUseProgram(_rend->shader_program_view()->shader_program()->program_id());
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);
      auto _imgID = ImageBank::get()->GetImage(_imgName);
      glBindTexture(GL_TEXTURE_2D, _imgID);
      glBindVertexArray(_VAOID);
      glDrawElements(GL_TRIANGLES, _vert_count, GL_UNSIGNED_INT, NULL);
      glBindVertexArray(0);
      glUseProgram(0);
      glDisable(GL_CULL_FACE);
   }

   void DrawTile(StringView _imgName, RenderID _VAOID, bool _depthTestOff) {
      auto _vert_count = 4;
      auto _rend = RendGroundView::get();
      if (_depthTestOff)
         glDisable(GL_DEPTH_TEST);
      else
         glEnable(GL_DEPTH_TEST);
      if (!_rend->is_batch_drawing()) {
         _rend->UseVAOBegin(_VAOID);
         glUniformMatrix4fv(
             _rend->location_projection(), 1, GL_FALSE,
             glm::value_ptr(CameraGL::get()->persp_matrix()));
         glUniformMatrix4fv(
             _rend->location_view(), 1, GL_FALSE, glm::value_ptr(CameraGL::get()->view_matrix()));
         glm::mat4 _model(1.0);
         glUniformMatrix4fv(_rend->location_model(), 1, GL_FALSE, glm::value_ptr(_model));
         glUniform1f(_rend->location_alpha(), 1.0f);
         auto _playerPos = Player::get()->pos().Multiply(k_tileSize);
         glm::vec3 _viewPos(
             _playerPos.x,
             _playerPos.y +
                 CalcTileAverageElevation(
                     Player::get()->pos().GetXZ().ToIntPoint(), Player::get()->world_location()),
             _playerPos.z);
         glUniform3fv(_rend->location_view_pos(), 1, glm::value_ptr(_viewPos));
         glm::vec3 _fogColorGL(
             RendGroundView::get()->fog_color_ground().r,
             RendGroundView::get()->fog_color_ground().g,
             RendGroundView::get()->fog_color_ground().b);
         glUniform3fv(_rend->location_fog_color(), 1, glm::value_ptr(_fogColorGL));
      }
      auto _imgID = ImageBank::get()->GetImage(_imgName);
      glBindTexture(GL_TEXTURE_2D, _imgID);
      glBindVertexArray(_VAOID);
      glDrawElements(GL_TRIANGLE_FAN, _vert_count, GL_UNSIGNED_INT, NULL);
      glBindVertexArray(0);
      if (!_rend->is_batch_drawing())
         _rend->UseVAOEnd();
   }

   void StartTileBatchDrawing() {
      auto _rend = RendGroundView::get();
      _rend->set_is_batch_drawing(true);
      glUseProgram(_rend->shader_program_view()->shader_program()->program_id());
      glUniformMatrix4fv(
          _rend->location_projection(), 1, GL_FALSE,
          glm::value_ptr(CameraGL::get()->persp_matrix()));
      glUniformMatrix4fv(
          _rend->location_view(), 1, GL_FALSE, glm::value_ptr(CameraGL::get()->view_matrix()));
      glm::mat4 model(1.0);
      glUniformMatrix4fv(_rend->location_model(), 1, GL_FALSE, glm::value_ptr(model));
      glUniform1f(_rend->location_alpha(), 1.0f);
      auto _playerPos = Player::get()->pos().Multiply(k_tileSize);
      auto _currMapLoc = Player::get()->world_location();
      auto _worldArea = World::get()->CurrWorldArea();
      auto _tileSize = k_tileSize;
      auto _mapOffsX = _currMapLoc.x * _worldArea->Width() * _tileSize;
      auto _mapOffsY = _currMapLoc.y * _worldArea->Height() * _tileSize;
      _playerPos.x += _mapOffsX;
      _playerPos.z += _mapOffsY;
      glm::vec3 _viewPos(
          _playerPos.x,
          _playerPos.y +
              CalcTileAverageElevation(
                  Player::get()->pos().GetXZ().ToIntPoint(), Player::get()->world_location()),
          _playerPos.z);
      glUniform3fv(_rend->location_view_pos(), 1, glm::value_ptr(_viewPos));
      glm::vec3 _fogColorGL(
          RendGroundView::get()->fog_color_ground().r, RendGroundView::get()->fog_color_ground().g,
          RendGroundView::get()->fog_color_ground().b);
      glUniform3fv(_rend->location_fog_color(), 1, glm::value_ptr(_fogColorGL));
      glUseProgram(_rend->shader_program_view()->shader_program()->program_id());
      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);
   }

   void StopTileBatchDrawing() {
      auto _rend = RendGroundView::get();
      _rend->set_is_batch_drawing(false);
      glUseProgram(0);
      glDisable(GL_CULL_FACE);
   }
}
