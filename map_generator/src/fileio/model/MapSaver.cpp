#include "MapSaver.h"
#include "conf/model/conf.h"
#include "world.structure/model/world.h"
namespace Narradia
{
    void MapSaver::SaveWorldMapToFile() {
        auto map_area = World::get()->curr_map_area();
        std::ofstream file;
        file.open(
            std::string(SDL_GetBasePath()) + "/" + kMapName + ".map",
            std::ofstream::out | std::ofstream::trunc);
        file << "<width>" << kMapWidth << "</width>\n";
        file << "<height>" << kMapHeight << "</height>\n";
        for (auto y = 0; y < kMapHeight; y++) {
            for (auto x = 0; x < kMapWidth; x++) {
                auto tile = map_area->GetTile(x, y);
                file << "<tile>\n";
                file << "   <ground>" << tile->ground() << "</ground>\n";
                file << "   <elevation>" << tile->elevation() << "</elevation>\n";
                file << "   <mob>\n";
                if (tile->mob()) {
                    file << "<type>" << tile->mob()->type() << "</type>\n";
                }
                else {
                    file << "<type>" << 0 << "</type>";
                }
                file << "   </mob>\n";
                file << "   <red>" << tile->color()->r << "</red>\n";
                file << "   <green>" << tile->color()->g << "</green>\n";
                file << "   <blue>" << tile->color()->b << "</blue>\n";
                file << "   <objects>\n";
                if (tile->object()) {
                    file << "      <object>\n";
                    file << "         <type>" << tile->object()->type() << "</type>\n";
                    file << "         <quantity>" << 1 << "</quantity>\n";
                    file << "      </object>\n";
                }
                file << "   </objects>\n";
                file << "</tile>\n";
            }
        }
        file.close();
    }
}
