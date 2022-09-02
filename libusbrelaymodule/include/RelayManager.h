#pragma once

#include <list>
#include <memory>

#include "IRelayManager.h"

#ifdef __linux__
#define DLL_EXPORT
#else
#define DLL_EXPORT __declspec(dllexport)
#endif

namespace nlab {

std::unique_ptr<IRelayManager> DLL_EXPORT CreateHidapiManagerForDcttechModules();

}

#undef DLL_EXPORT