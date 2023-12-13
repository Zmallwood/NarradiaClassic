#include "iscene.h"
namespace Narradia
{
    void IScene::UpdateGameLogic() {
        UpdateGameLogicDerived();
        scene_gui_->UpdateGameLogic();
    }
}
