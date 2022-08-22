#pragma once

#include <list>
#include <memory>

#include "IRelayModule.h"

namespace urm {

using IRelayModulePtr = std::shared_ptr<IRelayModule>;

class IRelayManager
{
public:
    virtual ~IRelayManager() = default;

    virtual std::list<IRelayModulePtr> GetModules() = 0;
};

} // namespace urm
