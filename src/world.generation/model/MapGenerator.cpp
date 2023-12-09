#include "MapGenerator.h"
#include "command/GenerateGrass.h"
#include "command/GenerateMobs.h"
#include "command/GenerateObjects.h"
#include "command/GenerateWater.h"

namespace Narradia {
    /**
     Generate all terrain and content for a MapArea.
    */
    void MapGenerator::GenerateMapArea(std::shared_ptr<MapArea> map_area) {
        GenerateGrass(map_area);
        GenerateWater(map_area);
        GenerateObjects(map_area);
        GenerateMobs(map_area);
    }
}
