#pragma once

namespace Narradia {

    using Render_ID = GLuint;

    using String = std::string;

    using String_View = std::string_view;

    template <class T>
    using Vector = std::vector<T>;

    template <class T>
    using Shared_Ptr = std::shared_ptr<T>;

    template <class T, class U>
    using Map = std::map<T, U>;

    template <class T>
    using Set = std::set<T>;

    template <class T>
    using Function = std::function<T>;

    using Exception = std::exception;

    template <class T, class... __Args>
    auto Make_Shared(__Args... args) {

        return std::make_shared<T>(args...);
    }

    template <class T>
    inline auto To_String(T arg) {

        return std::to_string(arg);
    }
}
