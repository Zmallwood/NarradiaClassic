#include "MapLoader.h"
#include "world.structure/model/map_area.h"
namespace Narradia
{
    void MapLoader::LoadWorldMapFromFile(std::shared_ptr<MapArea>& map_area) {
        std::ifstream file;
        file.open(std::string(SDL_GetBasePath()) + kMapName + ".map");
        std::string s;
        file >> s;
        auto width_str = s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1);
        auto width = std::stoi(width_str);
        file >> s;
        auto height_str = s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1);
        auto height = std::stoi(height_str);
        map_area = std::make_shared<MapArea>(width, height);
        for (auto y = 0; y < height; y++) {
            for (auto x = 0; x < width; x++) {
                auto tile = map_area->GetTile(x, y);
                std::string s;
                file >> s;
                while (s != "</tile>") {
                    if (s.find("<ground>") != std::string::npos) {
                        auto ground_type =
                            s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1);
                        tile->set_ground(ground_type);
                    }
                    else if (s.find("<elevation>") != std::string::npos) {
                        auto elevation = std::stof(
                            s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1));
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
                                mob_type = s2.substr(
                                    s2.find(">") + 1, s2.find_last_of("<") - s2.find(">") - 1);
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
                            tile->set_mob(std::make_shared<Mob>(mob_type));
                            map_area->mobs_mirror()->insert({tile->mob(), {x, y}});
                        }
                    }
                    else if (s.find("<red>") != std::string::npos) {
                        auto red = std::stof(
                            s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1));
                        tile->color()->r = red;
                    }
                    else if (s.find("<green>") != std::string::npos) {
                        auto green = std::stof(
                            s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1));
                        tile->color()->g = green;
                    }
                    else if (s.find("<blue>") != std::string::npos) {
                        auto blue = std::stof(
                            s.substr(s.find(">") + 1, s.find_last_of("<") - s.find(">") - 1));
                        tile->color()->b = blue;
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
                                object_type = s2.substr(
                                    s2.find(">") + 1, s2.find_last_of("<") - s2.find(">") - 1);
                            }
                            else if (s2.find("<quantity>") != std::string::npos) {
                                quantity = std::stoi(s2.substr(
                                    s2.find(">") + 1, s2.find_last_of("<") - s2.find(">") - 1));
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