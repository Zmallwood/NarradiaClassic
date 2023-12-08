#include "MapGenerator.h"
#include "functions/DoGenerateGrass.h"
#include "functions/DoGenerateWater.h"
#include "functions/DoGenerateObjects.h"
#include "functions/DoGenerateMobs.h"

namespace Narradia {
    /**
     * Generate all terrain and content for a MapArea.
     */
    void MapGenerator::GenerateMapArea(std::shared_ptr<MapArea> map_area) {
        DoGenerateGrass(map_area);
        DoGenerateWater(map_area);
        DoGenerateObjects(map_area);
        DoGenerateMobs(map_area);
    }
}
