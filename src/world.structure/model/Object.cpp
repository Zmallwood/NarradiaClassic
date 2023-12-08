#include "Object.h"

namespace Narradia {

    /**
     * Set type of objects.
     */
    Object::Object(std::string_view type)
        : type_(type) {
    }
}
