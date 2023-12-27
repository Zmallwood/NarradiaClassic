#if 1
#include "draw_image.h"
#include "assets/m/image_bank.h"
#include "render/v/renderer_2d_images_view.h"
#include "render/m/renderer_base.h"
#endif

namespace Narradia
{
   auto DrawImage(std::string_view image_name, RenderID rid, const RectF &dest, Color color) -> void
   {
      auto renderer = Renderer2DImagesView::get();
      auto renderer_base = renderer->renderer_base();
      auto gl_rect = dest.ToGLRectF();
      Vertex2F vertices[RendererBase::kNumVerticesInRectangle];
      vertices[0].position = {gl_rect.x, gl_rect.y - gl_rect.h};
      vertices[1].position = {gl_rect.x, gl_rect.y};
      vertices[2].position = {gl_rect.x + gl_rect.w, gl_rect.y};
      vertices[3].position = {gl_rect.x + gl_rect.w, gl_rect.y - gl_rect.h};
      vertices[0].uv = {0.0f, 1.0f};
      vertices[1].uv = {0.0f, 0.0f};
      vertices[2].uv = {1.0f, 0.0f};
      vertices[3].uv = {1.0f, 1.0f};
      glDisable(GL_DEPTH_TEST);
      auto image_id = ImageBank::get()->GetImage(image_name);
      glBindTexture(GL_TEXTURE_2D, image_id);
      auto indices = std::vector<int>(RendererBase::kNumVerticesInRectangle);
      std::iota(std::begin(indices), std::end(indices), 0);
      std::vector<float> positions;
      std::vector<float> colors;
      std::vector<float> uvs;
      for (auto &vertex : vertices)
      {
         positions.push_back(vertex.position.x);
         positions.push_back(vertex.position.y);
         colors.push_back(color.r);
         colors.push_back(color.g);
         colors.push_back(color.b);
         colors.push_back(color.a);
         uvs.push_back(vertex.uv.x);
         uvs.push_back(vertex.uv.y);
      }
      renderer->UseVAOBegin(rid);
      auto index_buffer_id = renderer_base->BufId(BufferTypes::Indices, rid);
      auto position_buffer_id = renderer_base->BufId(BufferTypes::Positions2D, rid);
      auto color_buffer_id = renderer_base->BufId(BufferTypes::Colors, rid);
      auto uv_buffer_id = renderer_base->BufId(BufferTypes::Uvs, rid);
      renderer->UpdateIndicesData(index_buffer_id, indices);
      renderer->UpdateData(
          position_buffer_id, positions, BufferTypes::Positions2D,
          Renderer2DImagesView::kLocationPosition);
      renderer->UpdateData(
          color_buffer_id, colors, BufferTypes::Colors, Renderer2DImagesView::kLocationColor);
      renderer->UpdateData(uv_buffer_id, uvs, BufferTypes::Uvs, Renderer2DImagesView::kLocationUv);
      glDrawElements(GL_TRIANGLE_FAN, RendererBase::kNumVerticesInRectangle, GL_UNSIGNED_INT, NULL);
      renderer->UseVAOEnd();
   }
}
