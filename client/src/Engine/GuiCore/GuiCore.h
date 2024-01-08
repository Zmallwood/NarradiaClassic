#pragma once

namespace Narradia {

   // Model

#if 1
   class GuiComponent {
     public:
      virtual void UpdateGameLogic() = 0;
   };

   class GuiButton : public GuiComponent {
     public:
      GuiButton(
          const StringView &text, RectF bounds, Function<void()> action,
          StringView img_name = "GuiButtonBack",
          StringView hovered_img_name = "GuiButtonBackHovered");
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
      StringView text_;
      RectF bounds_;
      Function<void()> action_;
      StringView img_name_;
      StringView hovered_img_name_;
      bool hovered_;
   };

   class GuiContainer : public GuiComponent {
     public:
      GuiContainer(PointF position, SizeF size)
          : position_(position),
            size_(size),
            gui_components_(MakeShared<Vec<SharedPtr<GuiComponent>>>()) {
      }
      void AddGuiComponent(SharedPtr<GuiComponent> comp);
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
      SharedPtr<Vec<SharedPtr<GuiComponent>>> gui_components_;
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
          StringView title, RectF bounds, bool destroy_on_close = false,
          StringView background_image_name = "PanelBg");
      ~GuiWindow();
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

      StringView title_ = "Unnamed window";
      bool visible_ = false;
      bool destroy_on_close_ = false;
      SharedPtr<GuiWindowCloseButton> gui_window_close_button_;
      StringView background_image_name_;
   };

   class GuiWindowCloseButton {
     public:
      GuiWindowCloseButton(GuiWindow *parent_window)
          : parent_window_(parent_window) {
      }
      ~GuiWindowCloseButton();
      void UpdateGameLogic();
      RectF Bounds() const;

      auto hovered() {
         return hovered_;
      }

     private:
      static constexpr float kWidth = 0.01f;
      GuiWindow *parent_window_;
      bool hovered_ = false;
   };

   class SceneGui {
     public:
      SceneGui()
          : gui_components_(MakeShared<Vec<SharedPtr<GuiComponent>>>()) {
      }
      void UpdateGameLogic();
      void AddGuiComponent(SharedPtr<GuiComponent> comp);
      void RemoveGuiComponent(GuiComponent *comp);

      auto gui_components() {
         return gui_components_;
      }

     private:
      SharedPtr<Vec<SharedPtr<GuiComponent>>> gui_components_;
   };
#endif

   // View

#if 1
   class GuiComponentV {
     public:
      virtual void Render() = 0;

      auto gui_component() {
         return gui_component_;
      }

      void set_gui_component(SharedPtr<GuiComponent> value) {
         gui_component_ = value;
      }

     protected:
      SharedPtr<GuiComponent> gui_component_;
   };

   class GuiButtonV : public GuiComponentV {
     public:
      GuiButtonV();
      void Render() override;

     private:
      RenderID rid_image;
      RenderID rid_label_text_;
   };

   class GuiContainerV : public GuiComponentV {
     protected:
      void Render() override;
      void AddGuiComponentView(SharedPtr<GuiComponentV> comp_view);

      void set_gui_container(SharedPtr<GuiContainer> value) {
         gui_container_ = value;
      }

     private:
      SharedPtr<GuiContainer> gui_container_;
      Vec<SharedPtr<GuiComponentV>> gui_component_views_;
   };

   class GuiMovableContainerV : public GuiContainerV {
     protected:
      void Render() override;
   };

   class GuiWindowCloseButtonV;

   class GuiWindowV : public GuiMovableContainerV {
     public:
      GuiWindowV();

      auto gui_window_close_button_view() {
         return gui_window_close_button_view_;
      }

     protected:
      virtual void RenderDerived() = 0;

     private:
      void Render() override;

      RenderID rid_background_;
      RenderID rid_title_bar_;
      RenderID rid_title_text_;
      SharedPtr<GuiWindowCloseButtonV> gui_window_close_button_view_;
   };

   class GuiWindowCloseButtonV {
     public:
      GuiWindowCloseButtonV();
      void Render();

      void set_model(SharedPtr<GuiWindowCloseButton> value) {
         model_ = value;
      }

     private:
      SharedPtr<GuiWindowCloseButton> model_;
      RenderID rid_close_btn_img_;
   };

   class SceneGuiV {
     public:
      void Render();
      void AddGuiComponentView(SharedPtr<GuiComponentV> comp_view);

      void set_scene_gui(SharedPtr<SceneGui> value) {
         scene_gui_ = value;
      }

     private:
      SharedPtr<SceneGui> scene_gui_;
      Vec<SharedPtr<GuiComponentV>> gui_component_views_;
   };
#endif

}
