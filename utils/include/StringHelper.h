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

#include <string>

namespace nkhlab {
namespace usbrelaymodule {
namespace utils {

class StringHelper
{
public:
    StringHelper() = delete;

    static std::string PrintBytes(uint8_t* bytes, size_t size);
    static std::string GetStrFromBytes(uint8_t* bytes, size_t size);
    static std::string PwstrToStr(wchar_t* pwstr);
    static std::string Sprintf(const char* fmt, ...);
};

} // namespace utils
} // namespace usbrelaymodule
} // namespace nkhlab