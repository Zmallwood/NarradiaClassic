#pragma once

namespace Narradia {
    class MapArea;

    class MapGenerator : public Singleton<MapGenerator> {
      public:
        void GenerateMapArea(std::shared_ptr<MapArea> map_area);
    };
}