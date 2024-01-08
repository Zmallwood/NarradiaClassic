#pragma once

namespace Narradia {

    template <class T>
    class Singleton {
      public:
        template <typename... U>
        static void Touch(U... args);
        static void Dispose();
        static std::shared_ptr<T> get();

      private:
        inline static std::shared_ptr<T> instance_;
    };

    template <class T>
    template <class... __Args>
    void Singleton<T>::Touch(__Args... args) {

        if (!instance_) {

            instance_ = std::make_shared<T>(args...);
            AddSingletonDisposeAction([&] { instance_.reset(); });
        }
    }

    template <class T>
    void Singleton<T>::Dispose() {

        if (instance_) {

            instance_.reset();
            instance_ = nullptr;
        }
    }

    template <class T>
    std::shared_ptr<T> Singleton<T>::get() {

        if (!instance_)
            Touch();
        return instance_;
    }
}
