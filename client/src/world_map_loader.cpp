#if 1
#include "world_map_loader.h"
#include "player.h"
#include "world-struct.h"
#endif

namespace Narradia
{
   WorldMapLoader::WorldMapLoader() {

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
            world_area_names_[x][y] = map_name;
         }
      }

      file.close();
   }
   void WorldMapLoader::LoadWorldMapFromFile(
       std::shared_ptr<WorldArea> &world_area, std::string map_name) {
      std::ifstream file;
      file.open(std::string(SDL_GetBasePath()) + map_name);
      std::string s;
      file >> s;
      auto width_str = s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1);
      auto width = std::stoi(width_str);
      file >> s;
      auto height_str = s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1);
      auto height = std::stoi(height_str);
      world_area = std::make_shared<WorldArea>(width, height);
      for (auto y = 0; y < height; y++) {
         for (auto x = 0; x < width; x++) {
            auto tile = world_area->GetTile(x, y);
            Point3F normal;
            std::string s;
            file >> s;
            while (s != "</tile>") {
               if (s.find("<ground>") != std::string::npos) {
                  auto ground_type =
                      s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1);
                  tile->set_ground(ground_type);
               }
               else if (s.find("<elevation>") != std::string::npos) {
                  auto elevation =
                      std::stof(s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1));
                  tile->set_elevation(elevation);
               }
               //                    else if (s.find("<roof>") != std::string::npos) {
               //                        auto roof_type = std::stoi(
               //                            s.substr(s.find(">") + 1, s.find_last_of("<") -
               //                            s.find(">") - 1));
               //                        tile->SetRoofType(roof_type);
               //                    }
               else if (s.find("<mob>") != std::string::npos) {
                  std::string s2;
                  std::string mob_type = "";
                  //                        int mob_type = 0;
                  //                        int spawn_x = -1;
                  //                        int spawn_y = -1;
                  while (s2 != "</mob>") {
                     if (s2.find("<type>") != std::string::npos) {
                        mob_type =
                            s2.substr(s2.find(">") + 1, s2.find_last_of("<") - s2.find(">") - 1);
                     }
                     //                            else if (s2.find("<spawnX>") !=
                     //                            std::string::npos) {
                     //                                spawn_x = std::stoi(s2.substr(
                     //                                    s2.find(">") + 1,
                     //                                    s2.find_last_of("<") -
                     //                                    s2.find(">") - 1));
                     //                            }
                     //                            else if (s2.find("<spawnY>") !=
                     //                            std::string::npos) {
                     //                                spawn_y = std::stoi(s2.substr(
                     //                                    s2.find(">") + 1,
                     //                                    s2.find_last_of("<") -
                     //                                    s2.find(">") - 1));
                     //                            }
                     file >> s2;
                  }
                  if (mob_type != "0") {
                     //tile->set_mob(std::make_shared<Mob>(mob_type));
                     //world_area->mobs_mirror()->insert({tile->mob(), {x, y}});
                  }
               }
               else if (s.find("<red>") != std::string::npos) {
                  auto red =
                      std::stof(s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1));
                  tile->color()->r = red;
               }
               else if (s.find("<green>") != std::string::npos) {
                  auto green =
                      std::stof(s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1));
                  tile->color()->g = green;
               }
               else if (s.find("<blue>") != std::string::npos) {
                  auto blue =
                      std::stof(s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1));
                  tile->color()->b = blue;
               }
               else if (s.find("</normal>") != std::string::npos) {
                  tile->set_normal(normal);
               }
               else if (s.find("<x>") != std::string::npos) {
                  auto x =
                      std::stof(s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1));
                  normal.x = x;
               }
               else if (s.find("<y>") != std::string::npos) {
                  auto y =
                      std::stof(s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1));
                  normal.y = y;
               }
               else if (s.find("<z>") != std::string::npos) {
                  auto z =
                      std::stof(s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1));
                  normal.z = z;
               }
               else if (s.find("<objects>") != std::string::npos) {
                  std::string s2;
                  // int object_type = 0;
                  std::string object_type;
                  int quantity = 0;
                  while (s2 != "</objects>") {
                     if (s2.find("</object>") != std::string::npos) {
                        tile->set_object(std::make_shared<Object>(object_type));
                     }
                     else if (s2.find("<type>") != std::string::npos) {
                        object_type =
                            s2.substr(s2.find(">") + 1, s2.find_last_of("<") - s2.find(">") - 1);
                     }
                     else if (s2.find("<quantity>") != std::string::npos) {
                        quantity = std::stoi(
                            s2.substr(s2.find(">") + 1, s2.find_last_of("<") - s2.find(">") - 1));
                     }
                     file >> s2;
                  }
               }
               file >> s;
            }
         }
      }
      file.close();
   }
}
