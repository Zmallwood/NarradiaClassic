#pragma once

namespace Narradia
{
    class MapArea;

    /**
     Randomly generates a complete MapArea with all its terrain and contents.
    */
    class MapGenerator : public Singleton<MapGenerator> {
      public:
        void GenerateMapArea(std::shared_ptr<MapArea> map_area);
    };
}
