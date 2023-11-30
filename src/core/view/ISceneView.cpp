#include "ISceneView.h"

namespace Narradia {
    /**
     * Render scenes deriving from this class.
     */
    void ISceneView::Render() {
        RenderDerived();
    }
}
