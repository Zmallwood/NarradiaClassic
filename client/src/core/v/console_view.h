#pragma once

namespace Narradia
{
   class ConsoleView : public Singleton<ConsoleView>
   {
     public:
      ConsoleView();

      auto Render() const -> void;

     private:
      RenderID rid_image_;
      RenderID rid_split_line_;
      RenderID rid_cmd_line_input_arrow_;
      RenderID rid_input_text_;
      std::vector<RenderID> rids_text_lines_;
   };
}
