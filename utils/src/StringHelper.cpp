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

#include "StringHelper.h"

#include <codecvt>
#include <iomanip>
#include <locale>
#include <sstream>
#include <stdarg.h>

namespace nkhlab {
namespace usbrelaymodule {
namespace utils {

std::string StringHelper::PrintBytes(uint8_t* bytes, size_t size)
{
    std::stringstream ss;

    ss << std::hex;
    for (size_t i = 0; i < size; ++i)
    {
        ss << std::setfill('0') << std::setw(2) << static_cast<int>(bytes[i]);
        if (i < size - 1) ss << " ";
    }

    return ss.str();
}

std::string StringHelper::GetStrFromBytes(uint8_t* bytes, size_t size)
{
    size_t actual_str_size{size};

    for (size_t i = 0; i < size; ++i)
    {
        if (bytes[i] == 0)
        {
            actual_str_size = i;
            break;
        }
    }

    return std::string(std::string(reinterpret_cast<char*>(&bytes[0]), actual_str_size));
}

std::string StringHelper::PwstrToStr(wchar_t* pwstr)
{
    std::string str = "(null)";
    if (pwstr)
    {
        // wide to UTF-8
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        str = converter.to_bytes(pwstr);
    }

    return str;
}

std::string StringHelper::Sprintf(const char* fmt, ...)
{
    const int LOG_BUFFER_SIZE = 512;

    char buffer[LOG_BUFFER_SIZE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, LOG_BUFFER_SIZE - 1, fmt, args);
    va_end(args);

    return std::string(buffer);
}

} // namespace utils
} // namespace usbrelaymodule
} // namespace nkhlab