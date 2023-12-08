#include "MapArea.h"
#include "configuration/model/Configuration.h"

namespace Narradia
{
    /**
     * Initializes internal map structures.
     */
    MapArea::MapArea()
        : mobs_mirror_(std::make_shared<std::map<std::shared_ptr<Mob>, Point>>()) {

        for (auto x = 0; x < kMapWidth; x++) {
            tiles_.push_back(std::vector<std::shared_ptr<Tile>>());

            for (auto y = 0; y < kMapHeight; y++) {
                tiles_.at(x).push_back(std::make_shared<Tile>());
            }
        }
    }

    /**
     * Returns pointer to specific tile at coordinate.
     */
    std::shared_ptr<Tile> MapArea::GetTile(int x, int y) {

        return tiles_.at(x).at(y);
    }

    std::shared_ptr<Tile> MapArea::GetTile(Point coord) {

        return GetTile(coord.x, coord.y);
    }

    bool MapArea::IsInsideMap(Point coord) {

        return coord.x < tiles_.size() && coord.y < tiles_.at(0).size();
    }
}
