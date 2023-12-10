#include "new_image.h"
#include "core.render/view/renderer_2d_images_view.h"
namespace Narradia {
  RenderID NewImage() {
    auto renderer = Renderer2DImagesView::Get();
    auto renderer_base = renderer->renderer_base();
    auto vao_id = renderer_base->GenerateNewVertexArrayId();
    renderer->UseVaoBegin(vao_id);
    auto index_buffer_id = renderer_base->GenerateNewBufferId(BufferTypes::Indices, vao_id);
    auto position_buffer_id = renderer_base->GenerateNewBufferId(BufferTypes::Positions2D, vao_id);
    auto color_buffer_id = renderer_base->GenerateNewBufferId(BufferTypes::Colors, vao_id);
    auto uv_buffer_id = renderer_base->GenerateNewBufferId(BufferTypes::Uvs, vao_id);
    renderer->SetIndicesData(index_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr);
    renderer->SetData(
        position_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr,
        BufferTypes::Positions2D);
    renderer->SetData(
        color_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr, BufferTypes::Colors);
    renderer->SetData(
        uv_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr, BufferTypes::Uvs);
    renderer->UseVaoEnd();
    return vao_id;
  }
}
