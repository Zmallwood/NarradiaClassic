#include "fileio/model/MapSaver.h"
#include "world.structure/model/world.h"

/**
 Entry.
*/
int main(int argc, char *argv[]) {
    std::cout << "Narradia Map Generator\n";
    std::cout << "======================\n";
    Narradia::World::Touch();
    std::cout << "World generation finished.\n";
    Narradia::MapSaver::Get()->SaveWorldMapToFile();
    std::cout << "World saved to file.\n";
}
