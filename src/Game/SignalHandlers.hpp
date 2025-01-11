#ifndef SIGNAL_HANDLERS_HPP
#define SIGNAL_HANDLERS_HPP

#include "Utils/Logger.hpp"

namespace SignalHandlers{
    // Example handler for AttackOrderComponent updates
    inline void onAttackOrderUpdate() {
        log_info << "signal detected";
    }

}

#endif // SIGNAL_HANDLERS_HPP