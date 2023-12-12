#include "singletons_cleanup.h"
namespace Narradia
{
    /**
     * @brief Holds all dispose functions which all of them will be executed on game exit.
     *
     */
    static std::vector<std::function<void()>> gDisposeActions;

    /**
     * @brief Called every time a singleton is created.
     *
     * @param[in] action Function which will be executed on game exit.
     */
    void AddSingletonDisposeAction(std::function<void()> action) {
        gDisposeActions.push_back(action);
    }

    /**
     * @brief Called at game exit.
     *
     */
    void DisposeAllSingletons() {
        for (auto &dispose_action : gDisposeActions)
            dispose_action();
    }
}
