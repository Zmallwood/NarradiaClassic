#pragma once
namespace Narradia
{
   class FPSCounterModuleView : public Singleton<FPSCounterModuleView>
   {
     public:
      FPSCounterModuleView();
      void Render();

     private:
      RenderID rid_text;
   };
}
