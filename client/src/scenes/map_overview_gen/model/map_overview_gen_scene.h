#pragma once
#include "../../../core/model/iscene.h"
namespace Narradia
{
   class MapOverviewGenScene : public IScene, public Singleton<MapOverviewGenScene> {
     private:
        void UpdateGameLogicDerived() override;
        void Finalize() override; 
   };
}
