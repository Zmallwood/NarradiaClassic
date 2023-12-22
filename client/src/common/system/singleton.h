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
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Create new instance if none exists.
      ///
      /// @tparam T Class to create instance of.
      ////////////////////////////////////////////////////////////////////////////////
      static auto Touch() -> void;

      static auto Dispose() -> void;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Get instance of class.
      ///
      /// @tparam T Class to get instance of.
      /// @return Pointer to instance of class T.
      ////////////////////////////////////////////////////////////////////////////////
      static auto get() -> std::shared_ptr<T>;

     private:
      inline static std::shared_ptr<T> instance_;
   };

   template <class T>
   auto Singleton<T>::Touch() -> void {
      if (!instance_) {
         instance_ = std::make_shared<T>();
         AddSingletonDisposeAction([&] { instance_.reset(); });
      }
   }

   template <class T>
   auto Singleton<T>::Dispose() -> void {
      if (instance_) {
         instance_.reset();
         instance_ = nullptr;
         std::cout << "disposed singleotn\n";
      }
   }

   template <class T>
   auto Singleton<T>::get() -> std::shared_ptr<T> {
      if (!instance_) // Create new instance if none exists
         Touch();
      return instance_;// Return weak_ptr to not increase ref count
   }
}
