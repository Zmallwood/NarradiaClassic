#pragma once
#include "core/v/iscene_view.h"
namespace Narradia
{
   class IntroSceneView : public ISceneView, public Singleton<IntroSceneView>
   {
     public:
      IntroSceneView();

     private:
      void RenderDerived() override;

      RenderID rid_background;
      RenderID rid_logo;
      RenderID rid_text;
   };
}
