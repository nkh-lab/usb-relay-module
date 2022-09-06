#pragma once

#include <list>
#include <memory>

#include "IRelayModule.h"

#ifdef __linux__
#define DLL_EXPORT
#else
#define DLL_EXPORT __declspec(dllexport)
#endif

namespace nlab {

using IRelayModulePtr = std::shared_ptr<IRelayModule>;
using IRelayModulePtrs = std::list<IRelayModulePtr>;

class DLL_EXPORT IRelayManager
{
public:
    virtual ~IRelayManager() = default;

    virtual IRelayModulePtrs GetModules() = 0;
};

} // namespace nlab

#undef DLL_EXPORT