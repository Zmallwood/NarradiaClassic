#pragma once

#include "Actors/Player.h"
#include "Configuration/Configuration.h"
#include "File_IO/World_Map_Rdr.h"

namespace Narradia {

    // Show World sub classes

#if 1

    // Show MapArea sub classes
#if 1

    // Show Tile sub classes
#if 1

    class Object {
      public:
        Object(String type)
            : type_(type) {
        }

        auto type() {
            return type_;
        }

        void set_type(String_View value) {
            type_ = value;
        }

      private:
        String type_ = "";
    };

    class TileEffect {
      public:
        String_View type;
        int ticks_started = 0;
    };

#endif

    class Mob;

    class Tile {
      public:
        Tile()
            : color_(Make_Shared<Color>()) {
        }

        void IncreaseElevation(float amount) {
            elevation_ += amount;
        }

        inline auto ground() {
            return ground_;
        }

        void set_ground(String value) {
            ground_ = value;
        }

        auto object() {
            return object_;
        }

        void set_object(Shared_Ptr<Object> value) {
            object_ = value;
        }

        auto mob() {
            return mob_;
        }

        void set_mob(Shared_Ptr<Mob> value) {
            mob_ = value;
        }

        auto elevation() {
            return elevation_;
        }

        void set_elevation(float value) {
            elevation_ = value;
        }

        auto tile_effect() {
            return tile_effect_;
        }

        void set_tile_effect(TileEffect value) {
            tile_effect_ = value;
        }

        auto rid() {
            return rid_;
        }

        void set_rid(Render_ID value) {
            rid_ = value;
        }

        auto normal() {
            return normal_;
        }
        void set_normal(Point3F value) {
            normal_ = value;
        }

        auto color() {
            return color_;
        }

      private:
        String ground_;
        Shared_Ptr<Object> object_;
        Shared_Ptr<Mob> mob_;
        float elevation_ = 0.0f;
        TileEffect tile_effect_;
        Render_ID rid_ = 0;
        Point3F normal_;
        Shared_Ptr<Color> color_;
    };

#endif

    class WorldArea {
      public:
        WorldArea(int width, int height)
            : mobs_mirror_(Make_Shared<Map<Shared_Ptr<Mob>, Point>>()) {
            for (auto x = 0; x < width; x++) {
                tiles_.push_back(Vector<Shared_Ptr<Tile>>());

                for (auto y = 0; y < height; y++) {
                    tiles_.at(x).push_back(Make_Shared<Tile>());
                }
            }
        }

        inline Shared_Ptr<Tile> GetTile(int x, int y) {
            try {
                return tiles_.at(x).at(y);
            } catch (Exception &e) {
                throw std::runtime_error("Tried to access tile with an invalid coordinate.");
            }
        }

        inline Shared_Ptr<Tile> GetTile(Point coord) {
            return GetTile(coord.x, coord.y);
        }

        inline bool IsInsideMap(Point coord) {
            return coord.x < tiles_.size() && coord.y < tiles_.at(0).size();
        }

        inline int Width() {
            return tiles_.size();
        }

        inline int Height() {
            return tiles_.at(0).size();
        }

        void ClearAllRIDs() {
            for (auto y = 0; y < Height(); y++) {
                for (auto x = 0; x < Width(); x++) {
                    tiles_.at(x).at(y)->set_rid(0);
                }
            }
        }

        auto mobs_mirror() {
            return mobs_mirror_;
        }

      private:
        Vector<Vector<Shared_Ptr<Tile>>> tiles_;
        Shared_Ptr<Map<Shared_Ptr<Mob>, Point>> mobs_mirror_;
    };

#endif

    class World : public Singleton<World> {
      public:
        World() {
            world_width_ = WorldMapRdr::get()->world_map_width();
            world_height_ = WorldMapRdr::get()->world_map_height();

            auto map_names = WorldMapRdr::get()->world_area_names();

            for (auto y = 0; y < world_height_; y++) {
                for (auto x = 0; x < world_width_; x++) {
                    world_areas_[x][y] = nullptr;

                    WorldMapRdr::get()->LoadWorldMapFromFile(world_areas_[x][y], map_names[x][y]);
                }
            }
        }

        inline Shared_Ptr<WorldArea> CurrWorldArea() {
            auto world_loc = Player::get()->world_location();

            return world_areas_[world_loc.x][world_loc.y];
        }

        Shared_Ptr<WorldArea> WorldAreaAt(Point location) {
            if (world_areas_.count(location.x) != 0)
                if (world_areas_.at(location.x).count(location.y) != 0)
                    return world_areas_[location.x][location.y];

            return nullptr;
        }

        auto world_width() {
            return world_width_;
        }

        auto world_height() {
            return world_height_;
        }

        auto world_areas() {
            return world_areas_;
        }

      private:
        Map<int, Map<int, Shared_Ptr<WorldArea>>> world_areas_;
        int world_width_ = -1;
        int world_height_ = -2;
    };

}
