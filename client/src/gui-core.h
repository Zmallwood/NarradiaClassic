#pragma once

namespace Narradia
{
   class GuiComponent {
     public:
      virtual void UpdateGameLogic() = 0;
   };

   class GuiButton : public GuiComponent {
     public:
      GuiButton(
          const std::string_view &text, RectF bounds, std::function<void()> action,
          std::string_view img_name = "GuiButtonBack",
          std::string_view hovered_img_name = "GuiButtonBackHovered");
      void UpdateGameLogic() override;
      auto text() {
         return text_;
      }
      auto bounds() {
         return bounds_;
      }
      auto img_name() {
         return img_name_;
      }
      auto hovered_img_name() {
         return hovered_img_name_;
      }
      auto hovered() {
         return hovered_;
      }

     private:
      std::string_view text_;
      RectF bounds_;
      std::function<void()> action_;
      std::string_view img_name_;
      std::string_view hovered_img_name_;
      bool hovered_;
   };

   class GuiContainer : public GuiComponent {
     public:
      GuiContainer(PointF position, SizeF size)
          : position_(position),
            size_(size),
            gui_components_(std::make_shared<std::vector<std::shared_ptr<GuiComponent>>>()) {
      }
      void AddGuiComponent(std::shared_ptr<GuiComponent> comp);
      RectF Bounds();
      auto position() {
         return position_;
      }
      auto size() {
         return size_;
      }
      auto gui_components() {
         return gui_components_;
      }

     protected:
      void UpdateGameLogic() override;
      void set_position(PointF value) {
         position_ = value;
      }

     private:
      PointF position_;
      SizeF size_;
      std::shared_ptr<std::vector<std::shared_ptr<GuiComponent>>> gui_components_;
   };

   class GuiMovableContainer : public GuiContainer {
     public:
      GuiMovableContainer(RectF rel_dragable_area, PointF position, SizeF size)
          : GuiContainer(position, size),
            rel_dragable_area_(rel_dragable_area) {
      }

     protected:
      void UpdateGameLogic() override;

     private:
      RectF rel_dragable_area_;
      bool movement_trigger_ = false;
      bool is_moving_ = false;
      PointF mouse_pos_start_moving_;
      PointF self_pos_start_moving_;
   };

   class GuiWindowCloseButton;

   class GuiWindow : public GuiMovableContainer {
     public:
      GuiWindow(
          std::string_view title, RectF bounds, bool destroy_on_close = false,
          std::string_view background_image_name = "PanelBg");
      void Hide();
      void ToggleVisibility();
      RectF AbsTitleBarBounds();
      auto destroy_on_close() {
         return destroy_on_close_;
      }
      auto visible() {
         return visible_;
      }
      auto background_image_name() {
         return background_image_name_;
      }
      auto title() {
         return title_;
      }
      auto gui_window_close_button() {
         return gui_window_close_button_;
      }

      static constexpr float kTitleBarHeight = 0.03f;
      static constexpr float kMargin = 0.005f;

     protected:
      void UpdateGameLogic() override;

     private:
      virtual void UpdateGameLogicDerived() = 0;

      std::string_view title_ = "Unnamed window";
      bool visible_ = false;
      bool destroy_on_close_ = false;
      std::shared_ptr<GuiWindowCloseButton> gui_window_close_button_;
      std::string_view background_image_name_;
   };

   class GuiWindowCloseButton {
     public:
      GuiWindowCloseButton(std::shared_ptr<GuiWindow> parent_window)
          : parent_window_(parent_window) {
      }
      void UpdateGameLogic();
      auto hovered() {
         return hovered_;
      }
      RectF Bounds() const;

     private:
      static constexpr float kWidth = 0.01f;
      std::shared_ptr<GuiWindow> parent_window_;
      bool hovered_ = false;
   };

   class SceneGui {
     public:
      SceneGui()
          : gui_components_(std::make_shared<std::vector<std::shared_ptr<GuiComponent>>>()) {
      }
      void UpdateGameLogic();
      void AddGuiComponent(std::shared_ptr<GuiComponent> comp);
      void RemoveGuiComponent(std::shared_ptr<GuiComponent> comp);
      auto gui_components() {
         return gui_components_;
      }

     private:
      std::shared_ptr<std::vector<std::shared_ptr<GuiComponent>>> gui_components_;
   };
}
