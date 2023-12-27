#if 1
#include "new_rect.h"
#include "render/v/renderer_2d_solid_colors_view.h"
#endif

namespace Narradia
{
   auto NewRect() -> RenderID
   {
      auto renderer = Renderer2DSolidColorsView::get();
      auto renderer_base = renderer->renderer_base();
      auto vao_id = renderer_base->GenNewVAOId();
      renderer->UseVAOBegin(vao_id);
      auto index_buffer_id = renderer_base->GenNewBufId(BufferTypes::Indices, vao_id);
      auto position_buffer_id = renderer_base->GenNewBufId(BufferTypes::Positions2D, vao_id);
      auto color_buffer_id = renderer_base->GenNewBufId(BufferTypes::Colors, vao_id);
      renderer->SetIndicesData(index_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr);
      renderer->SetData(
          position_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr,
          BufferTypes::Positions2D);
      renderer->SetData(
          color_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr, BufferTypes::Colors);
      renderer->UseVAOEnd();
      return vao_id;
   }
}
