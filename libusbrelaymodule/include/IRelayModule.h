/*
 * Copyright (C) 2022 https://github.com/nkh-lab
 *
 * This is free software. You can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 */

#pragma once

#include <string>
#include <vector>

#ifdef __linux__
#define DLL_EXPORT
#else
#define DLL_EXPORT __declspec(dllexport)
#endif

namespace nkhlab {
namespace usbrelaymodule {

class DLL_EXPORT IRelayModule
{
public:
    virtual ~IRelayModule() = default;

    virtual std::string GetInfo() = 0;

    virtual bool GetNameAndChannels(std::string& module_name, std::vector<bool>& channels) = 0;

    virtual bool SetName(const std::string& name) = 0;

    //
    // channel_idx - starts from 0
    //
    virtual bool SetChannel(size_t channel_idx, bool state) = 0;
};

} // namespace usbrelaymodule
} // namespace nkhlab

#undef DLL_EXPORT