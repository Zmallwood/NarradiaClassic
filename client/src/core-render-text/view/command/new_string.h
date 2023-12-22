#pragma once
#include "core-render-text/view/renderer_text.h"
#include "core-render/view/command/new_image.h"
#include "create_get_blank_texture.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Prepares resources for a new string to be rendered.
   ///
   /// @return RID for the newly created string, which will be provided to the DrawString()
   /// function.
   ////////////////////////////////////////////////////////////////////////////////
   auto NewString() -> RenderID;
}
