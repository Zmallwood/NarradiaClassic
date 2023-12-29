#if 1
#include "fill_rect.h"
#include "render/renderer_2d_solid_colors_v.h"
#endif

namespace Narradia
{
   auto DrawRect(RenderID vao_id, RectF rect, Color color) -> void
   {
      auto renderer = Renderer2DSolidColorsV::get();
      auto renderer_base = renderer->renderer_base();
      auto gl_rect = rect.ToGLRectF();
      Vertex2F vertices[RendererBase::kNumVerticesInRectangle];
      vertices[0].pos = {gl_rect.x, gl_rect.y - gl_rect.h};
      vertices[1].pos = {gl_rect.x, gl_rect.y};
      vertices[2].pos = {gl_rect.x + gl_rect.w, gl_rect.y};
      vertices[3].pos = {gl_rect.x + gl_rect.w, gl_rect.y - gl_rect.h};
      glDisable(GL_DEPTH_TEST);
      auto indices = std::vector<int>(RendererBase::kNumVerticesInRectangle);
      std::iota(std::begin(indices), std::end(indices), 0);
      std::vector<float> positions;
      std::vector<float> colors;
      for (auto &vertex : vertices)
      {
         positions.push_back(vertex.pos.x);
         positions.push_back(vertex.pos.y);
         colors.push_back(color.r);
         colors.push_back(color.g);
         colors.push_back(color.b);
         colors.push_back(color.a);
      }
      renderer->UseVAOBegin(vao_id);
      auto index_buffer_id = renderer_base->BufId(BufferTypes::Indices, vao_id);
      auto position_buffer_id = renderer_base->BufId(BufferTypes::Positions2D, vao_id);
      auto color_buffer_id = renderer_base->BufId(BufferTypes::Colors, vao_id);
      renderer->UpdateIndicesData(index_buffer_id, indices);
      renderer->UpdateData(
          position_buffer_id, positions, BufferTypes::Positions2D,
          Renderer2DSolidColorsV::kLocationPosition);
      renderer->UpdateData(
          color_buffer_id, colors, BufferTypes::Colors, Renderer2DSolidColorsV::kLocationColor);
      glDrawElements(GL_LINE_STRIP, RendererBase::kNumVerticesInRectangle, GL_UNSIGNED_INT, NULL);
      renderer->UseVAOEnd();
   }
}
