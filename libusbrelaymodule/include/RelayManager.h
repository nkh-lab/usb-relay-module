#pragma once

#include <list>
#include <memory>

#include "IRelayManager.h"

#ifdef __linux__
#define DLL_EXPORT
#else
#define DLL_EXPORT __declspec(dllexport)
#endif

namespace nkhlab {
namespace usbrelaymodule {

using IRelayManagerPtr = std::unique_ptr<IRelayManager>;

IRelayManagerPtr DLL_EXPORT CreateHidapiManagerForDcttechModules();

} // namespace usbrelaymodule
} // namespace nkhlab

#undef DLL_EXPORT