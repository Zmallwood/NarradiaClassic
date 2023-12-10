#pragma once
#include "MapArea.h"

namespace Narradia {
    /**
     Top most object in the world map hierchical structure.
    */
    class World : public Singleton<World> {
      public:
        World();

        auto curr_map_area() {
            return curr_map_area_;
        }

      private:
        std::shared_ptr<MapArea> curr_map_area_ = nullptr;
    };
}
