#pragma once
#include "RendererBaseView.h"

namespace Narradia {
    class RendererTilesView : public RendererBaseView,
                              public Singleton<RendererTilesView> {
      public:
        RendererTilesView();

        ~RendererTilesView();

        RenderId NewTile();

        void SetGeometryTile(
            RenderId vao_id, Vertex3F &v0, Vertex3F &v1, Vertex3F &v2,
            Vertex3F &v3, Point3F &normal00, Point3F &normal10,
            Point3F &normal11, Point3F &normal01) const;

        void DrawTile(
            std::string_view image_name, RenderId vao_id,
            bool depth_test_off = false) const;

        void UpdateDrawTile(
            std::string_view image_name, RenderId vao_id, Vertex3F &v0,
            Vertex3F &v1, Vertex3F &v2, Vertex3F &v3, Point3F &normal00,
            Point3F &normal10, Point3F &normal11, Point3F &normal01,
            bool depth_test_off = false) const;

        void StartBatchDrawing();

        void StopBatchDrawing();

      private:
        void DrawImagePolygon(
            std::string_view image_name, RenderId vao_id, int vertex_count,
            bool depth_test_off = false) const;

        RenderId NewImagePolygon(int num_vertices);

        void SetGeometryImagePolygon(
            RenderId vao_id, std::vector<Vertex3F> &vertices) const;

        const int kLocationPosition = 0;
        const int kLocationColor = 1;
        const int kLocationUv = 2;
        const int kLocationNormal = 3;
        const Color kFogColorGround = Colors::mild_blue;

        int location_projection_ = -1;
        int location_view_ = -1;
        int location_model_ = -1;
        int location_alpha_ = -1;
        int location_view_pos_ = -1;
        int location_fog_color_ = -1;
        bool is_batch_drawing_ = false;
    };
}
