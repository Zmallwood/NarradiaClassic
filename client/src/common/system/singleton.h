#pragma once
#include <memory>
namespace Narradia
{
    /**
     * @brief Singleton templated class.
     *
     * @tparam T Class to create singleton of.
     */
    template <class T>
    class Singleton {
      public:
        static void Touch();
        static std::shared_ptr<T> Get();
      private:
        inline static std::shared_ptr<T> instance_;
    };

    /**
     * @brief Create new instance if non exists.
     *
     * @tparam T Class to create template of.
     */
    template <class T>
    void Singleton<T>::Touch() {
        if (!instance_) {
            instance_ = std::make_shared<T>();
            AddSingletonDisposeAction([&] { instance_.reset(); });
        }
    }

    /**
     * @brief Get instance of object.
     *
     * @tparam T Class to get instance of.
     */
    template <class T>
    std::shared_ptr<T> Singleton<T>::Get() {
        if (!instance_) // Create new instance if none exists
            Touch();
        return std::weak_ptr<T>(instance_).lock(); // Return weak_ptr to not increase ref count
    }
}
