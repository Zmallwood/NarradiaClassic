#pragma once

namespace Narradia {
   using RenderID = GLuint;
   using String = std::string;
   using StringView = std::string_view;
   template <class T>
   using Vec = std::vector<T>;
   template <class T>
   using SharedPtr = std::shared_ptr<T>;
   template <class T, class U>
   using Map = std::map<T, U>;
   template <class T>
   using Set = std::set<T>;
   template <class T>
   using Function = std::function<T>;
   using Exception = std::exception;

   template <class T, class... __Args>
   auto MakeShared(__Args... args) {

      return std::make_shared<T>(args...);
   }

   template <class T>
   inline auto ToString(T arg) {

      return std::to_string(arg);
   }
}
