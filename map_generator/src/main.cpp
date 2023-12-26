#include "fileio/m/MapSaver.h"
#include "world-struct/m/world.h"
#include "world-generation/m/map_generator.h"

/**
 Entry.
*/
int main(int argc, char *argv[]) {
   std::cout << "Narradia Map Generator\n";
   std::cout << "======================\n";
   srand(time(0));
   using namespace Narradia;
   World::Touch();
   MapGenerator::get()->GenerateMapArea(World::get()->curr_map_area());
   std::cout << "World generation finished.\n";
   MapSaver::get()->SaveWorldMapToFile();
   std::cout << "World saved to file.\n";
   DisposeAllSingletons();
}
