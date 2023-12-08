#include "MapGenerator.h"
#include "functions/GenerateGrass.h"
#include "functions/GenerateMobs.h"
#include "functions/GenerateObjects.h"
#include "functions/GenerateWater.h"

namespace Narradia {
    /**
     * Generate all terrain and content for a MapArea.
     */
    void MapGenerator::GenerateMapArea(std::shared_ptr<MapArea> map_area) {
        GenerateGrass(map_area);
        GenerateWater(map_area);
        GenerateObjects(map_area);
        GenerateMobs(map_area);
    }
}
