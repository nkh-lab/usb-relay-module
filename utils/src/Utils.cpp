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

#include "Utils.h"

#include <codecvt>
#include <iomanip>
#include <locale>
#include <sstream>
#include <stdarg.h>

namespace nkhlab {
namespace usbrelaymodule {
namespace utils {

std::string PrintBytes(uint8_t* bytes, size_t size)
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

std::string GetStrFromBytes(uint8_t* bytes, size_t size)
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

std::string PwstrToStr(wchar_t* pwstr)
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

std::string Sprintf(const char* fmt, ...)
{
    const int LOG_BUFFER_SIZE = 512;

    char buffer[LOG_BUFFER_SIZE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, LOG_BUFFER_SIZE - 1, fmt, args);
    va_end(args);

    return std::string(buffer);
}

void SplitModuleChannelStr(const std::string& module_channel, std::string& module, size_t& channel)
{
    const char* kModuleChannelDelimiter = "_";

    size_t delimiter_pos = module_channel.find_first_of(kModuleChannelDelimiter);

    if (delimiter_pos != std::string::npos)
    {
        module = module_channel.substr(0, delimiter_pos);
        channel = std::stoi(module_channel.substr(delimiter_pos + 1));
    }
    else
    {
        module = module_channel;
        channel = 0;
    }
}

} // namespace utils
} // namespace usbrelaymodule
} // namespace nkhlab