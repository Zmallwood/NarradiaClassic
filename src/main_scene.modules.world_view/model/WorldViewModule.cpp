#include "WorldViewModule.h"
#include "Camera.h"

namespace Narradia {
    void WorldViewModule::UpdateGameLogic() { Camera::Get()->UpdateGameLogic(); }
}
