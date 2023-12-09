#pragma once

namespace Narradia
{
    /**
    View component of the TextOutBox.
    */
    class TextOutBoxView : public Singleton<TextOutBoxView> {
      public:
        TextOutBoxView();
        void Render() const;

      private:
        RenderId rid_image_;
        RenderId rid_split_line_;
        RenderId rid_cmd_line_input_arrow_;
        RenderId rid_input_text_;
        std::vector<RenderId> rids_text_lines_;
    };
}
