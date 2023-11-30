#include "IScene.h"

namespace Narradia {
    /**
     * Update game logic from scenes deriving from this class.
     */
    void IScene::UpdateGameLogic() {
        UpdateGameLogicDerived();
    }
}
