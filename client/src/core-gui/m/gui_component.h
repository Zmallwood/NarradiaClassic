#pragma once
namespace Narradia
{
   class GuiComponent
   {
     public:
      virtual auto UpdateGameLogic() -> void = 0;
   };
}
