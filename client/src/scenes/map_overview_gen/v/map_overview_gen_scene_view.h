#pragma once
#include "../../../core/v/iscene_view.h"
namespace Narradia
{
   class MapOverviewGenSceneView : public ISceneView, public Singleton<MapOverviewGenSceneView>
   {
     private:
      void RenderDerived() override;
   };
}
