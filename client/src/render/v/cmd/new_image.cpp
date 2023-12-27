#if 1
#include "new_image.h"
#include "render/v/renderer_2d_images_view.h"
#endif

namespace Narradia
{
   auto NewImage() -> RenderID
   {
      auto renderer = Renderer2DImagesView::get();
      auto renderer_base = renderer->renderer_base();
      auto vao_id = renderer_base->GenNewVAOId();
      renderer->UseVAOBegin(vao_id);
      auto index_buffer_id = renderer_base->GenNewBufId(BufferTypes::Indices, vao_id);
      auto position_buffer_id = renderer_base->GenNewBufId(BufferTypes::Positions2D, vao_id);
      auto color_buffer_id = renderer_base->GenNewBufId(BufferTypes::Colors, vao_id);
      auto uv_buffer_id = renderer_base->GenNewBufId(BufferTypes::Uvs, vao_id);
      renderer->SetIndicesData(index_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr);
      renderer->SetData(
          position_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr,
          BufferTypes::Positions2D);
      renderer->SetData(
          color_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr, BufferTypes::Colors);
      renderer->SetData(
          uv_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr, BufferTypes::Uvs);
      renderer->UseVAOEnd();
      return vao_id;
   }
}
