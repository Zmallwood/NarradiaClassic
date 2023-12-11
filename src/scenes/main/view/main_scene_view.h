#pragma once
#include "core/view/iscene_view.h"
namespace Narradia {
  /**
   View for MainScene.
  */
  class MainSceneView : public ISceneView, public Singleton<MainSceneView> {
   public:
    MainSceneView();

   private:
    void RenderDerived() override;

    RenderID rid_level_text;
  };
}
