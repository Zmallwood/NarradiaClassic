#pragma once
#include "MapArea.h"

namespace Narradia {
    class World : public Singleton<World> {
      public:
        World();

        std::shared_ptr<MapArea> curr_map_area() {
            return curr_map_area_;
        }

      private:
        std::shared_ptr<MapArea> curr_map_area_ = nullptr;
    };
}