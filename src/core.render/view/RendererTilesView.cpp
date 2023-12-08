#include "RendererTilesView.h"
#include "CameraGL.h"
#include "core.assets/model/ImageBank.h"
#include "functions/DrawImagePolygon.h"
#include "functions/SetImagePolygonGeometry.h"
#include "world.actors/model/Player.h"

namespace Narradia
{
    RendererTilesView::RendererTilesView() {

        const GLchar *vertex_shader_source =
#include "core.render.shaders/model/TilesVertex.glsl"
            ;
        const GLchar *fragment_shader_source =
#include "core.render.shaders/model/TilesFragment.glsl"
            ;
        GetShaderProgramView()->Create(vertex_shader_source, fragment_shader_source);
        location_projection_ = GetUniformLocation("projection");
        location_view_ = GetUniformLocation("view");
        location_model_ = GetUniformLocation("model");
        location_alpha_ = GetUniformLocation("mAlpha");
        location_view_pos_ = GetUniformLocation("viewPos");
        location_fog_color_ = GetUniformLocation("fogColor");
    }

    RendererTilesView::~RendererTilesView() {

        CleanupBase();
    }
}
