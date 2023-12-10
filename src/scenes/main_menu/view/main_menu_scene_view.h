#pragma once
#include "core/view/iscene_view.h"
namespace Narradia {
  /**
   View for MainMenuScene.
  */
  class MainMenuSceneView : public ISceneView, public Singleton<MainMenuSceneView> {
   public:
    MainMenuSceneView();

   private:
    void RenderDerived() override;

    RenderID rid_background;
    RenderID rid_logo;
  };
}
