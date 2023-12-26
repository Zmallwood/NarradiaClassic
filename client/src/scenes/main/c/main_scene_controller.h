#pragma once
#include "core/c/iscene_controller.h"
namespace Narradia
{
   class MainSceneController : public ISceneController, public Singleton<MainSceneController>
   {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };
}
