#pragma once

namespace Narradia
{
    /**
     Singleton templated class.
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
     Create new instance if none exists.
    */
    template <class T>
    void Singleton<T>::Touch()
    {
        if (!instance_) {
            instance_ = std::make_shared<T>();
            AddSingletonDisposeAction([&] { instance_.reset(); });
        }
    }

    /**
     Get instance of object.
    */
    template <class T>
    std::shared_ptr<T> Singleton<T>::Get()
    {
        if (!instance_) // Create new instance if none exists
            Touch();

        return std::weak_ptr<T>(instance_).lock(); // Return weak_ptr to not increase ref count
    }
}
