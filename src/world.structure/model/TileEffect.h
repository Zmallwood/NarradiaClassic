#pragma once

namespace Narradia
{
    class TileEffect
    {
        public:
            std::string_view type;
            int ticks_started = 0;
    };
}
