#include "RendererTilesView.h"
#include "CameraGL.h"
#include "command/DrawImagePolygon.h"
#include "command/SetImagePolygonGeometry.h"
#include "core.assets/model/ImageBank.h"
#include "world.actors/model/Player.h"

namespace Narradia
{
    RendererTilesView::RendererTilesView()
    {
        const GLchar *vertex_shader_source =
#include "core.render.shaders/model/TilesVertex.inc.cpp"
            ;
        const GLchar *fragment_shader_source =
#include "core.render.shaders/model/TilesFragment.inc.cpp"
            ;
        GetShaderProgramView()->Create(vertex_shader_source, fragment_shader_source);
        location_projection_ = GetUniformLocation("projection");
        location_view_ = GetUniformLocation("view");
        location_model_ = GetUniformLocation("model");
        location_alpha_ = GetUniformLocation("mAlpha");
        location_view_pos_ = GetUniformLocation("viewPos");
        location_fog_color_ = GetUniformLocation("fogColor");
    }

    RendererTilesView::~RendererTilesView() { CleanupBase(); }
}
