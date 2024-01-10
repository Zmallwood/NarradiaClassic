#include "ImagesRendering.h"
#include "nRendImagesView.h"
#include "Core/Assets/nModelBank.h"
#include "Core/Assets/nImageBank.h"

namespace Narradia {
   RenderID NewImage() {
      auto _rend = nRendImagesView::get();
      auto _rendBase = _rend->RendererBase();
      auto _VAOID = _rendBase->GenNewVAOId();
      _rend->UseVAOBegin(_VAOID);
      auto _indexBufID = _rendBase->GenNewBufId(nBufTypes::Indices, _VAOID);
      auto _posBufID = _rendBase->GenNewBufId(nBufTypes::Positions2D, _VAOID);
      auto _colorBufID = _rendBase->GenNewBufId(nBufTypes::Colors, _VAOID);
      auto _uvBufID = _rendBase->GenNewBufId(nBufTypes::Uvs, _VAOID);
      _rend->SetIndicesData(_indexBufID, nRendBase::kNumVerticesInRectangle, nullptr);
      _rend->SetData(
          _posBufID, nRendBase::kNumVerticesInRectangle, nullptr, nBufTypes::Positions2D);
      _rend->SetData(
          _colorBufID, nRendBase::kNumVerticesInRectangle, nullptr, nBufTypes::Colors);
      _rend->SetData(_uvBufID, nRendBase::kNumVerticesInRectangle, nullptr, nBufTypes::Uvs);
      _rend->UseVAOEnd();
      return _VAOID;
   }

   void DrawImage(StringView _imgName, RenderID _RID, const RectF &_dest, Color _color) {
      auto _rend = nRendImagesView::get();
      auto _rendBase = _rend->RendererBase();
      auto _GLRect = _dest.ToGLRectF();
      Vertex2F _verts[nRendBase::kNumVerticesInRectangle];
      _verts[0].pos = {_GLRect.x, _GLRect.y - _GLRect.h};
      _verts[1].pos = {_GLRect.x, _GLRect.y};
      _verts[2].pos = {_GLRect.x + _GLRect.w, _GLRect.y};
      _verts[3].pos = {_GLRect.x + _GLRect.w, _GLRect.y - _GLRect.h};
      _verts[0].uv = {0.0f, 1.0f};
      _verts[1].uv = {0.0f, 0.0f};
      _verts[2].uv = {1.0f, 0.0f};
      _verts[3].uv = {1.0f, 1.0f};
      glDisable(GL_DEPTH_TEST);
      auto _imgID = nImageBank::get()->GetImage(_imgName);
      glBindTexture(GL_TEXTURE_2D, _imgID);
      auto _indices = std::vector<int>(nRendBase::kNumVerticesInRectangle);
      std::iota(std::begin(_indices), std::end(_indices), 0);
      Vec<float> _positions;
      Vec<float> _colors;
      Vec<float> _uvs;
      for (auto &_vert: _verts) {
         _positions.push_back(_vert.pos.x);
         _positions.push_back(_vert.pos.y);
         _colors.push_back(_color.r);
         _colors.push_back(_color.g);
         _colors.push_back(_color.b);
         _colors.push_back(_color.a);
         _uvs.push_back(_vert.uv.x);
         _uvs.push_back(_vert.uv.y);
      }
      _rend->UseVAOBegin(_RID);
      auto _indexBufID = _rendBase->BufId(nBufTypes::Indices, _RID);
      auto _posBufID = _rendBase->BufId(nBufTypes::Positions2D, _RID);
      auto _colorBufID = _rendBase->BufId(nBufTypes::Colors, _RID);
      auto _uvBufID = _rendBase->BufId(nBufTypes::Uvs, _RID);
      _rend->UpdateIndicesData(_indexBufID, _indices);
      _rend->UpdateData(
          _posBufID, _positions, nBufTypes::Positions2D, nRendImagesView::kLocationPosition);
      _rend->UpdateData(
          _colorBufID, _colors, nBufTypes::Colors, nRendImagesView::kLocationColor);
      _rend->UpdateData(_uvBufID, _uvs, nBufTypes::Uvs, nRendImagesView::kLocationUv);
      glDrawElements(GL_TRIANGLE_FAN, nRendBase::kNumVerticesInRectangle, GL_UNSIGNED_INT, NULL);
      _rend->UseVAOEnd();
   }
}
