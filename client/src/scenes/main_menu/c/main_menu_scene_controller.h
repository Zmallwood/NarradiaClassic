#pragma once
#include "core/c/iscene_controller.h"
namespace Narradia
{
   class MainMenuSceneController : public ISceneController,
                                   public Singleton<MainMenuSceneController>
   {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };
}
