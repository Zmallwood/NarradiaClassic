#pragma once

#include "core/c/iscene_controller.h"

namespace Narradia
{
   class IntroSceneController : public ISceneController, public Singleton<IntroSceneController>
   {
     private:
      void OnEnter() override;
      void UpdateGameFlowDerived() override;
   };
}
