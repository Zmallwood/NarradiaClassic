#pragma once

namespace Narradia {
   RenderID NewImage();
   // clang-format off
   void DrawImage(
      StringView _imgName,
      RenderID _RID,
      const RectF &_dest,
      Color _color = Colors::white);
   // clang-format on
}
