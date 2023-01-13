/*
 * Copyright (C) 2023 https://github.com/nkh-lab
 *
 * This is free software. You can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 */

#pragma once

#include <fstream>
#include <mutex>

namespace nkhlab {
namespace usbrelaymodule {
namespace impl {

template <typename TResource>
class SynchronizedResource
{
public:
    SynchronizedResource(TResource&& res)
        : res_{std::move(res)}
    {
    }
    ~SynchronizedResource() = default;

    std::unique_lock<std::mutex> GetLock() { return std::unique_lock<std::mutex>(mutex_); }
    TResource& GetResource() { return res_; }

private:
    TResource res_;
    std::mutex mutex_;
};

using SynchronizedString = SynchronizedResource<std::string>;

} // namespace impl
} // namespace usbrelaymodule
} // namespace nkhlab