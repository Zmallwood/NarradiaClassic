#include "NewString.h"
#include "../RendererText.h"
#include "CreateGetBlankTexture.h"
#include "core.render/view/command/NewImage.h"

namespace Narradia {
    /**
     Prepares resources for a new string to be rendered.
    */
    RenderId NewString() {
        auto unique_name = CreateGetBlankTexture();
        auto rendid_image_rect = NewImage();
        RendererText::Get()->unique_name_ids()->insert({rendid_image_rect, unique_name});

        return rendid_image_rect;
    }
}
