#pragma once

#include "core/c/iscene_controller.h"

namespace Narradia
{
   class MapOverViewGenSceneController : public ISceneController,
                                         public Singleton<MapOverViewGenSceneController>
   {
     public:
      void OnEnter() override;

     private:
      void UpdateGameFlowDerived() override;
   };
}
