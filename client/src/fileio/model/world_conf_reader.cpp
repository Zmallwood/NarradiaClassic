#include "world_conf_reader.h"
namespace Narradia
{
   WorldConfReader::WorldConfReader() {

      std::ifstream file;
      file.open(std::string(SDL_GetBasePath()) + kFileName);

      while (true) {
         std::string s;
         file >> s;
         if (file.eof())
            break;
         if (s.substr(0, 5) == "Width")
            world_map_width_ = std::stoi(s.substr(6));
         else if (s.substr(0, 6) == "Height")
            world_map_height_ = std::stoi(s.substr(7));
         else {
            auto x = std::stoi(s.substr(0, s.find(',')));
            auto y = std::stoi(s.substr(s.find(',') + 1, s.find('=') - s.find(',') - 1));
            auto map_name = s.substr(s.find('=') + 1);
            map_area_names_[x][y] = map_name;
         }
      }

      file.close();
   }
}
