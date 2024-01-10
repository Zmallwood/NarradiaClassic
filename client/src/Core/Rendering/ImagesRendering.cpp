#include "ImagesRendering.h"
#include "RendImagesView.h"
#include "Core/Assets/nModelBank.h"
#include "Core/Assets/nImageBank.h"

namespace Narradia {
   RenderID NewImage() {
      auto _rend = RendImagesView::get();
      auto _rendBase = _rend->renderer_base();
      auto _VAOID = _rendBase->GenNewVAOId();
      _rend->UseVAOBegin(_VAOID);
      auto _indexBufID = _rendBase->GenNewBufId(BufferTypes::Indices, _VAOID);
      auto _posBufID = _rendBase->GenNewBufId(BufferTypes::Positions2D, _VAOID);
      auto _colorBufID = _rendBase->GenNewBufId(BufferTypes::Colors, _VAOID);
      auto _uvBufID = _rendBase->GenNewBufId(BufferTypes::Uvs, _VAOID);
      _rend->SetIndicesData(_indexBufID, RendBase::kNumVerticesInRectangle, nullptr);
      _rend->SetData(
          _posBufID, RendBase::kNumVerticesInRectangle, nullptr, BufferTypes::Positions2D);
      _rend->SetData(
          _colorBufID, RendBase::kNumVerticesInRectangle, nullptr, BufferTypes::Colors);
      _rend->SetData(_uvBufID, RendBase::kNumVerticesInRectangle, nullptr, BufferTypes::Uvs);
      _rend->UseVAOEnd();
      return _VAOID;
   }

   void DrawImage(StringView _imgName, RenderID _RID, const RectF &_dest, Color _color) {
      auto _rend = RendImagesView::get();
      auto _rendBase = _rend->renderer_base();
      auto _GLRect = _dest.ToGLRectF();
      Vertex2F _verts[RendBase::kNumVerticesInRectangle];
      _verts[0].pos = {_GLRect.x, _GLRect.y - _GLRect.h};
      _verts[1].pos = {_GLRect.x, _GLRect.y};
      _verts[2].pos = {_GLRect.x + _GLRect.w, _GLRect.y};
      _verts[3].pos = {_GLRect.x + _GLRect.w, _GLRect.y - _GLRect.h};
      _verts[0].uv = {0.0f, 1.0f};
      _verts[1].uv = {0.0f, 0.0f};
      _verts[2].uv = {1.0f, 0.0f};
      _verts[3].uv = {1.0f, 1.0f};
      glDisable(GL_DEPTH_TEST);
      auto _imgID = ImageBank::get()->GetImage(_imgName);
      glBindTexture(GL_TEXTURE_2D, _imgID);
      auto _indices = std::vector<int>(RendBase::kNumVerticesInRectangle);
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
      auto _indexBufID = _rendBase->BufId(BufferTypes::Indices, _RID);
      auto _posBufID = _rendBase->BufId(BufferTypes::Positions2D, _RID);
      auto _colorBufID = _rendBase->BufId(BufferTypes::Colors, _RID);
      auto _uvBufID = _rendBase->BufId(BufferTypes::Uvs, _RID);
      _rend->UpdateIndicesData(_indexBufID, _indices);
      _rend->UpdateData(
          _posBufID, _positions, BufferTypes::Positions2D, RendImagesView::kLocationPosition);
      _rend->UpdateData(
          _colorBufID, _colors, BufferTypes::Colors, RendImagesView::kLocationColor);
      _rend->UpdateData(_uvBufID, _uvs, BufferTypes::Uvs, RendImagesView::kLocationUv);
      glDrawElements(GL_TRIANGLE_FAN, RendBase::kNumVerticesInRectangle, GL_UNSIGNED_INT, NULL);
      _rend->UseVAOEnd();
   }
}
