#include "ColorsRendering.h"
#include "RendColorsView.h"

namespace Narradia {
   RenderID NewRect() {
      auto _rend = RendColorsView::get();
      auto _rend_base = _rend->renderer_base();
      auto _VAOID = _rend_base->GenNewVAOId();
      _rend->UseVAOBegin(_VAOID);
      auto _indexBuffID = _rend_base->GenNewBufId(BufferTypes::Indices, _VAOID);
      auto _posBuffID = _rend_base->GenNewBufId(BufferTypes::Positions2D, _VAOID);
      auto _colorBuffID = _rend_base->GenNewBufId(BufferTypes::Colors, _VAOID);
      _rend->SetIndicesData(_indexBuffID, RendBase::kNumVerticesInRectangle, nullptr);
      _rend->SetData(
          _posBuffID, RendBase::kNumVerticesInRectangle, nullptr, BufferTypes::Positions2D);
      _rend->SetData(
          _colorBuffID, RendBase::kNumVerticesInRectangle, nullptr, BufferTypes::Colors);
      _rend->UseVAOEnd();
      return _VAOID;
   }

   void DrawRect(RenderID _VAOID, RectF _rect, Color _color) {
      auto _rend = RendColorsView::get();
      auto _rend_base = _rend->renderer_base();
      auto _GLRect = _rect.ToGLRectF();
      Vertex2F _verts[RendBase::kNumVerticesInRectangle];
      _verts[0].pos = {_GLRect.x, _GLRect.y - _GLRect.h};
      _verts[1].pos = {_GLRect.x, _GLRect.y};
      _verts[2].pos = {_GLRect.x + _GLRect.w, _GLRect.y};
      _verts[3].pos = {_GLRect.x + _GLRect.w, _GLRect.y - _GLRect.h};
      glDisable(GL_DEPTH_TEST);
      auto _indices = std::vector<int>(RendBase::kNumVerticesInRectangle);
      std::iota(std::begin(_indices), std::end(_indices), 0);
      Vec<float> _positions;
      Vec<float> _colors;
      for (auto &_vert: _verts) {
         _positions.push_back(_vert.pos.x);
         _positions.push_back(_vert.pos.y);
         _colors.push_back(_color.r);
         _colors.push_back(_color.g);
         _colors.push_back(_color.b);
         _colors.push_back(_color.a);
      }
      _rend->UseVAOBegin(_VAOID);
      auto _indexBuffID = _rend_base->BufId(BufferTypes::Indices, _VAOID);
      auto _posBuffID = _rend_base->BufId(BufferTypes::Positions2D, _VAOID);
      auto _colorBuffID = _rend_base->BufId(BufferTypes::Colors, _VAOID);
      _rend->UpdateIndicesData(_indexBuffID, _indices);
      _rend->UpdateData(
          _posBuffID, _positions, BufferTypes::Positions2D, RendColorsView::kLocationPosition);
      _rend->UpdateData(
          _colorBuffID, _colors, BufferTypes::Colors, RendColorsView::kLocationColor);
      glDrawElements(GL_LINE_STRIP, RendBase::kNumVerticesInRectangle, GL_UNSIGNED_INT, NULL);
      _rend->UseVAOEnd();
   }

   void FillRect(RenderID _VAOID, RectF _rect, Color _color) {
      auto _rend = RendColorsView::get();
      auto _rend_base = _rend->renderer_base();
      auto _GLRect = _rect.ToGLRectF();
      Vertex2F _verts[RendBase::kNumVerticesInRectangle];
      _verts[0].pos = {_GLRect.x, _GLRect.y - _GLRect.h};
      _verts[1].pos = {_GLRect.x, _GLRect.y};
      _verts[2].pos = {_GLRect.x + _GLRect.w, _GLRect.y};
      _verts[3].pos = {_GLRect.x + _GLRect.w, _GLRect.y - _GLRect.h};
      glDisable(GL_DEPTH_TEST);
      auto _indices = std::vector<int>(RendBase::kNumVerticesInRectangle);
      std::iota(std::begin(_indices), std::end(_indices), 0);
      Vec<float> _positions;
      Vec<float> _colors;
      for (auto &_vert: _verts) {
         _positions.push_back(_vert.pos.x);
         _positions.push_back(_vert.pos.y);
         _colors.push_back(_color.r);
         _colors.push_back(_color.g);
         _colors.push_back(_color.b);
         _colors.push_back(_color.a);
      }
      _rend->UseVAOBegin(_VAOID);
      auto _indexBuffID = _rend_base->BufId(BufferTypes::Indices, _VAOID);
      auto _posBuffID = _rend_base->BufId(BufferTypes::Positions2D, _VAOID);
      auto _colorBuffID = _rend_base->BufId(BufferTypes::Colors, _VAOID);
      _rend->UpdateIndicesData(_indexBuffID, _indices);
      _rend->UpdateData(
          _posBuffID, _positions, BufferTypes::Positions2D, RendColorsView::kLocationPosition);
      _rend->UpdateData(
          _colorBuffID, _colors, BufferTypes::Colors, RendColorsView::kLocationColor);
      glDrawElements(GL_TRIANGLE_FAN, RendBase::kNumVerticesInRectangle, GL_UNSIGNED_INT, NULL);
      _rend->UseVAOEnd();
   }
}
