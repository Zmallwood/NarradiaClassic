#pragma once

#include "world.h"

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

      void set_use_fixed_camera_distance(bool value) {
         use_fixed_camera_distance_ = value;
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
      bool use_fixed_camera_distance_ = false;

      const float kFixedCameraDistance = 1300.0f;
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
      inline void DrawGroundTileOutsideWorldArea(int x, int y, int dloc_x, int dloc_y);
      inline void DrawModelsTileOutsideWorldArea(int x, int y, int dloc_x, int dloc_y);
      inline void DrawGround(SharedPtr<Tile> tile, Point coord);
      inline void DrawTileSymbols(SharedPtr<Tile> tile, Point coord);

      int render_distance_ = 30;
      Vec<Vec<RenderID>> rids_tiles;
      Vec<Vec<RenderID>> rids_tile_symbols;

     private:
      void DrawAllGround();
      void DrawAllModels();
      void DrawObjects(SharedPtr<Tile> tile, Point coord, int dloc_x = 0, int dloc_y = 0);
      void DrawPlayer();

      RenderID rid_back_gradient;
      const float kTinyDistance = 0.001f;
      static constexpr int kGroundSimpleK = 6;
      bool simplified_ground_ = false;
   };

#endif
}
