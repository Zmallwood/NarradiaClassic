#include "new_rect.h"
#include "../renderer_2d_solid_colors_view.h"

namespace Narradia {
  /**
   Prepares resources for a new colored rectangle, later
   to be rendered, returning an id.
  */
  RenderID NewRect() {
    auto renderer = Renderer2DSolidColorsView::Get();
    auto renderer_base = renderer->renderer_base();
    auto vao_id = renderer_base->GenerateNewVertexArrayId();
    renderer->UseVaoBegin(vao_id);
    auto index_buffer_id = renderer_base->GenerateNewBufferId(BufferTypes::Indices, vao_id);
    auto position_buffer_id = renderer_base->GenerateNewBufferId(BufferTypes::Positions2D, vao_id);
    auto color_buffer_id = renderer_base->GenerateNewBufferId(BufferTypes::Colors, vao_id);
    renderer->SetIndicesData(index_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr);
    renderer->SetData(
        position_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr,
        BufferTypes::Positions2D);
    renderer->SetData(
        color_buffer_id, RendererBase::kNumVerticesInRectangle, nullptr, BufferTypes::Colors);
    renderer->UseVaoEnd();
    return vao_id;
  }
}
