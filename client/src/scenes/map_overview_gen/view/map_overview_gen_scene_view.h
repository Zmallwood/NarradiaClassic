#pragma once
#include "../../../core/view/iscene_view.h"
namespace Narradia
{
   class MapOverviewGenSceneView : public ISceneView, public Singleton<MapOverviewGenSceneView> {
      private:
        void RenderDerived() override;
   };
}
