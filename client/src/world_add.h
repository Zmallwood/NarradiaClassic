#pragma once

namespace Narradia
{
   // Model
#if 1
   class WorldAdd : public S<WorldAdd> {
     public:
      WorldAdd();
      void UpdateGameLogic();
   };

   class TileSquare {
     public:
      TileSquare(int x, int y) {

         coords._00 = {x, y};
         coords._10 = {x + 1, y};
         coords._11 = {x + 1, y + 1};
         coords._01 = {x, y + 1};
      }

      Square<Point> coords;
   };

   // Show Camera class
#if 1
   class Camera : public S<Camera> {
     public:
      void UpdateGameLogic();

      auto horizontal_angle_deg() {
         return horizontal_angle_deg_;
      }

      void set_horizontal_angle_deg(float value) {
         horizontal_angle_deg_ = value;
      }

      auto vertical_angle_deg() {
         return vertical_angle_deg_;
      }

      void set_vertical_angle_deg(float value) {
         vertical_angle_deg_ = value;
      }

      auto camera_distance() {
         return camera_distance_;
      }

      void set_camera_distance(float value) {
         camera_distance_ = value;
      }

     private:
      void SetPerspMat();
      void SetViewMat();
      Point3F GetCameraPos();

      float camera_height_ = 16.0f;
      float used_fov_ = 130.0f;
      float camera_distance_ = 9.0f;
      float horizontal_angle_deg_ = 0.0f;
      float vertical_angle_deg_ = 160.0f;
   };
#endif
#endif

   // View
#if 1
   class Tile;

   class WorldAddV : public S<WorldAddV> {
     public:
      WorldAddV(bool simplified_ground = false);
      void Render();
      void InitCurrWorldArea();

      auto render_distance() {
         return render_distance_;
      }

      void set_render_distance(int value) {
         render_distance_ = value;
      }

     private:
      void DrawGroundTileOutsideWorldArea(int x, int y, int dloc_x, int dloc_y);
      void DrawModelsTileOutsideWorldArea(int x, int y, int dloc_x, int dloc_y);
      void DrawAllGround();
      void DrawAllModels();
      void DrawGround(std::shared_ptr<Tile> tile, Point coord);
      void DrawObjects(std::shared_ptr<Tile> tile, Point coord, int dloc_x = 0, int dloc_y = 0);
      void DrawPlayer();
      void DrawTileSymbols(std::shared_ptr<Tile> tile, Point coord);

      std::vector<std::vector<RenderID>> rids_tiles;
      std::vector<std::vector<RenderID>> rids_tile_symbols;
      int render_distance_ = 30;
      bool simplified_ground_ = false;
      const float kTinyDistance = 0.001f;
      static constexpr int kGroundSimpleK = 6;
   };
#endif
}
