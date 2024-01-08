#include "Gui_Main_Pg.h"
#include "Engine/Rendering/Colors_Rendering.h"
#include "Engine/Rendering/Images_Rendering.h"
#include "Engine/Rendering/Text_Rendering.h"
#include "Math/Calc.h"
#include "World_Structure/Actors/Player.h"
#include "World_Structure/World_Structure.h"

namespace Narradia {

    // Model

#if 1
// Gui components
#if 1
    // StatusPanel
#if 1
    void StatusPanel::UpdateGameLogic() {
    }
#endif

    // ExperienceBar
#if 1
    void ExperienceBar::UpdateGameLogic() {
    }
#endif
#endif
// Gui windows
#if 1
    // GuiWindowWorldMap
#if 1
    void GuiWindowWorldMap::UpdateGameLogicDerived() {
    }
#endif
#endif
#endif

    // View

#if 1
// Gui components
#if 1
    // StatusPanelV
#if 1
    StatusPanelV::StatusPanelV() {
        rid_background_image_ = NewImage();
        rid_health_text_ = NewString();
        rid_stamina_text_ = NewString();
        rid_health_bar_ = NewRect();
        rid_stamina_bar_ = NewRect();
        rid_health_bar_filled_ = NewImage();
        rid_stamina_bar_filled_ = NewImage();
        rid_player_name_ = NewString();
        rid_level_label_ = NewString();
        rid_level_ = NewString();
    }

    void StatusPanelV::Render() {
        auto player = Player::get();

        DrawImage("PanelBg", rid_background_image_, StatusPanel::kBoundsPanel);

        DrawString(
            rid_player_name_, player->name(),
            StatusPanel::kBoundsPanel.GetPosition().Translate(0.01f, 0.02f));

        auto level_text = To_String(GetCurrentLevel(player->experience()));

        DrawString(
            rid_level_label_, "Level",
            StatusPanel::kBoundsPanel.GetPosition().Translate(0.01f, 0.05f), Colors::white, false,
            FontSizes::_40);

        DrawString(
            rid_level_, level_text, StatusPanel::kBoundsPanel.GetPosition().Translate(0.06f, 0.05f),
            Colors::yellow, false, FontSizes::_40);

        DrawString(rid_health_text_, "Health", {0.01f, 0.11f});
        DrawString(rid_stamina_text_, "Stamina", {0.01f, 0.14f});

        auto hp_bar_filled_bounds = StatusPanel::kHpBarBounds.WithWidth(
            (player->health()) / player->max_health() * StatusPanel::kHpBarBounds.w);

        auto stamina_bar_filled_bounds = StatusPanel::kStaminaBarBounds.WithWidth(
            (player->stamina()) / player->max_stamina() * StatusPanel::kStaminaBarBounds.w);

        FillRect(rid_health_bar_, StatusPanel::kHpBarBounds, Colors::black);
        DrawImage("Red", rid_health_bar_filled_, hp_bar_filled_bounds);
        FillRect(rid_stamina_bar_, StatusPanel::kStaminaBarBounds, Colors::black);
        DrawImage("Yellow", rid_stamina_bar_filled_, stamina_bar_filled_bounds);
    }
#endif

    // ExperienceBarV
#if 1
    ExperienceBarV::ExperienceBarV() {
        rid_unfilled_area_ = NewRect();
        rid_filled_area_ = NewImage();
        rid_text_ = NewString();
    }

    void ExperienceBarV::Render() {
        auto unfilled_area =
            RectF{0.0f, 1.0f - ExperienceBar::kBarHeight, 1.0f, ExperienceBar::kBarHeight};

        FillRect(rid_unfilled_area_, unfilled_area, Colors::dark_gray);

        auto experience_progress = GetFractionalExpProgress(Player::get()->experience());

        auto filled_area = RectF{
            0.0f, 1.0f - ExperienceBar::kBarHeight, experience_progress, ExperienceBar::kBarHeight};

        DrawImage("Green", rid_filled_area_, filled_area);

        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << (experience_progress * 100) << " %";
        String progress_text = stream.str();

        DrawString(rid_text_, progress_text, unfilled_area.GetCenter(), Colors::white, true);
    }
#endif
#endif
// Gui windows
#if 1
    // GuiWindowWorldMapV
#if 1
    GuiWindowWorldMapV::GuiWindowWorldMapV() {
        gui_window_close_button_view()->set_model(
            GuiWindowWorldMap::get()->gui_window_close_button());

        rid_img_ = NewImage();

        auto world_w = World::get()->world_width();
        auto world_h = World::get()->world_height();

        for (auto y = 0; y < world_h; y++) {
            for (auto x = 0; x < world_w; x++) {
                rids_rectangles_.push_back(NewRect());
                rids_images_.push_back(NewImage());
            }
        }

        rid_player_ = NewRect();
        rid_player_outline_ = NewRect();
    }

    void GuiWindowWorldMapV::RenderDerived() {
        auto model = static_pointer_cast<GuiWindow>(gui_component_);

        auto world_w = World::get()->world_width();
        auto world_h = World::get()->world_height();

        auto bounds = model->Bounds();
        bounds.y += GuiWindow::kTitleBarHeight + GuiWindow::kMargin;
        bounds.h -= GuiWindow::kTitleBarHeight + 3 * GuiWindow::kMargin;

        auto cell_width = bounds.w / world_w;
        auto cell_height = WidthToHeight(cell_width);

        if (world_h * cell_height > bounds.h) {
            cell_height = bounds.h / world_h;
            cell_width = HeightToWidth(cell_height);
        }

        auto i = 0;

        for (auto y = 0; y < world_h; y++) {
            for (auto x = 0; x < world_w; x++) {
                DrawImage(
                    "WorldMapImage" + To_String(x) + "_" + To_String(y), rids_images_[i],
                    {bounds.x + x * cell_width, bounds.y + y * cell_height, cell_width,
                     cell_height});

                DrawRect(
                    rids_rectangles_[i],
                    {bounds.x + x * cell_width, bounds.y + y * cell_height, cell_width,
                     cell_height},
                    Colors::black);

                i++;
            }
        }

        auto player_pos = Player::get()->pos();

        auto map_area = World::get()->world_areas()[Player::get()->world_location().x]
                                                   [Player::get()->world_location().y];

        auto tile_width = cell_width / map_area->Width();
        auto tile_height = cell_height / map_area->Height();
        auto marker_size = 0.005f;

        auto rect = RectF{
            bounds.x + Player::get()->world_location().x * cell_width + player_pos.x * tile_width,
            bounds.y + Player::get()->world_location().y * cell_height + player_pos.z * tile_height,
            marker_size, marker_size};

        FillRect(rid_player_, rect, Colors::yellow);
        DrawRect(rid_player_outline_, rect, Colors::black);
    }
#endif
#endif
#endif

}
