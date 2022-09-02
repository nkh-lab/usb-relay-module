#include "utils.h"

#include <iomanip>
#include <sstream>
#include <stdarg.h>

namespace nlab {
namespace utils {

std::string BytesToStr(uint8_t* bytes, size_t size)
{
    std::stringstream ss;

    ss << std::hex;
    for (int i = 0; i < size; ++i)
    {
        ss << std::setfill('0') << std::setw(2) << static_cast<int>(bytes[i]);
        if (i < size - 1) ss << " ";
    }

    return ss.str();
}

std::string PwstrToStr(wchar_t* pwstr)
{
    std::string str = "(null)";
    if (pwstr)
    {
        std::wstring wstr = std::wstring(pwstr);
        str = std::string(wstr.begin(), wstr.end());
    }

    return str;
}

std::string Sprintf(const char* fmt, ...)
{
    const int LOG_BUFFER_SIZE = 256;

    char buffer[LOG_BUFFER_SIZE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, LOG_BUFFER_SIZE - 1, fmt, args);
    va_end(args);

    return std::string(buffer);
}

} // namespace utils
} // namespace nlab