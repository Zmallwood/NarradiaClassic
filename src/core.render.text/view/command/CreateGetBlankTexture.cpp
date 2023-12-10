#include "CreateGetBlankTexture.h"
#include "core.assets/model/ImageBank.h"

namespace Narradia {
    /**
     Creates and returns unique name for a new blank texture.
    */
    std::string CreateGetBlankTexture() {
        static int id_counter = 0;
        auto id = id_counter++;
        auto unique_name = "RenderedImage" + std::to_string(id);
        ImageBank::Get()->CreateBlankTextImage(unique_name);
        return unique_name;
    }
}
