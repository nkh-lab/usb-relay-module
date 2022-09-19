#pragma once

#include <list>
#include <memory>

#include "IRelayModule.h"

#ifdef __linux__
#define DLL_EXPORT
#else
#define DLL_EXPORT __declspec(dllexport)
#endif

namespace nkhlab {
namespace usbrelaymodule {

using IRelayModulePtr = std::shared_ptr<IRelayModule>;
using IRelayModulePtrs = std::list<IRelayModulePtr>;

class DLL_EXPORT IRelayManager
{
public:
    virtual ~IRelayManager() = default;

    virtual IRelayModulePtrs GetModules() = 0;
};

} // namespace usbrelaymodule
} // namespace nkhlab

#undef DLL_EXPORT