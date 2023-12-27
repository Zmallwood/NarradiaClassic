#pragma once

#include "core/v/iscene_view.h"

namespace Narradia
{
   class MainSceneView : public ISceneView, public Singleton<MainSceneView>
   {
     public:
      MainSceneView();

     private:
      void RenderDerived() override;
   };
}
