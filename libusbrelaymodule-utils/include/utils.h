#pragma once

#include <string>

#define NOT_USED(x) static_cast<void>(x)

namespace urm {
namespace utils {

std::string BytesToStr(uint8_t* bytes, size_t size);
std::string PwstrToStr(wchar_t* pwstr);

} // namespace utils
} // namespace urm