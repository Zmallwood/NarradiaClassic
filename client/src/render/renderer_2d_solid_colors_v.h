#pragma once

#include "renderer_base_v.h"

namespace Narradia
{
   class Renderer2DSolidColorsV : public RendererBaseV, public S<Renderer2DSolidColorsV>
   {
     public:
      Renderer2DSolidColorsV();
      ~Renderer2DSolidColorsV();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
   };

   auto NewRect() -> RenderID;

   auto DrawRect(RenderID vao_id, RectF rect, Color color) -> void;

   auto FillRect(RenderID vao_id, RectF rect, Color color) -> void;
}
