#pragma once

namespace Narradia {
   template <class T>
   class Singleton {
     public:
      template <typename... U>
      static void Touch(U... _args);
      static void Dispose();
      static std::shared_ptr<T> get();

     private:
      inline static std::shared_ptr<T> m_instance;
   };

   template <class T>
   template <class... __Args>
   void Singleton<T>::Touch(__Args... _args) {
      if (!m_instance) {
         m_instance = std::make_shared<T>(_args...);
         AddSingletonDisposeAction([&] { m_instance.reset(); });
      }
   }
   template <class T>
   void Singleton<T>::Dispose() {
      if (m_instance) {
         m_instance.reset();
         m_instance = nullptr;
      }
   }
   template <class T>
   std::shared_ptr<T> Singleton<T>::get() {

      if (!m_instance)
         Touch();
      return m_instance;
   }
}
