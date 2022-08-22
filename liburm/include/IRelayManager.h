#pragma once

#include <list>
#include <memory>

#include "IRelayModule.h"

#ifdef __linux__
#define DLL_EXPORT
#else
#define DLL_EXPORT __declspec(dllexport)
#endif

namespace urm {

using IRelayModulePtr = std::shared_ptr<IRelayModule>;

class DLL_EXPORT IRelayManager
{
public:
    virtual ~IRelayManager() = default;

    virtual std::list<IRelayModulePtr> GetModules() = 0;
};

} // namespace urm

#undef DLL_EXPORT