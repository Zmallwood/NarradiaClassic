#include "MapArea.h"
#include "configuration/model/Configuration.h"

namespace Narradia {
    MapArea::MapArea()
        : mobs_mirror_(
              std::make_shared<std::map<std::shared_ptr<Mob>, Point>>()) {
        for (auto x = 0; x < kMapWidth; x++) {
            tiles_.push_back(std::vector<std::shared_ptr<Tile>>());

            for (auto y = 0; y < kMapHeight; y++) {
                tiles_.at(x).push_back(std::make_shared<Tile>());
            }
        }
    }

    std::shared_ptr<Tile> MapArea::GetTile(int x, int y) {
        return tiles_.at(x).at(y);
    }
}
