#include "SetTileGeometry.h"
#include "SetImagePolygonGeometry.h"

namespace Narradia
{
    void SetTileGeometry(
        RenderId vao_id, Vertex3F &v0, Vertex3F &v1, Vertex3F &v2, Vertex3F &v3, Point3F &normal00,
        Point3F &normal10, Point3F &normal11, Point3F &normal01) {

        std::vector<Vertex3F> vertices;
        v0.normal = normal00;
        v1.normal = normal10;
        v2.normal = normal11;
        v3.normal = normal01;
        vertices.push_back(v0);
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        SetImagePolygonGeometry(vao_id, vertices);
    }
}
