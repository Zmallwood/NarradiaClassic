#pragma once
#include <memory>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Singleton templated class.
   ///
   /// @tparam T Class to create singleton of.
   ////////////////////////////////////////////////////////////////////////////////
   template <class T>
   class Singleton {
     public:
      static auto Touch() -> void;

      static auto get() -> std::shared_ptr<T>;

     private:
      inline static std::shared_ptr<T> instance_;
   };

   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Create new instance if none exists.
   ///
   /// @tparam T Class to create instance of.
   ////////////////////////////////////////////////////////////////////////////////
   template <class T>
   auto Singleton<T>::Touch() -> void {
      if (!instance_) {
         instance_ = std::make_shared<T>();
         AddSingletonDisposeAction([&] { instance_.reset(); });
      }
   }

   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Get instance of class.
   ///
   /// @tparam T Class to get instance of.
   ////////////////////////////////////////////////////////////////////////////////
   template <class T>
   auto Singleton<T>::get() -> std::shared_ptr<T> {
      if (!instance_) // Create new instance if none exists
         Touch();
      return std::weak_ptr<T>(instance_).lock(); // Return weak_ptr to not increase ref count
   }
}
