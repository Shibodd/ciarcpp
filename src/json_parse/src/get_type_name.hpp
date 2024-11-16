#ifndef CIARCPP_PARSE_GETTYPENAME_HPP
#define CIARCPP_PARSE_GETTYPENAME_HPP

// https://stackoverflow.com/a/66551751

#include <string_view>

template <typename T>
constexpr auto get_type_name() -> std::string_view
{
#if defined(__clang__)
    constexpr auto prefix = std::string_view{"[T = "};
    constexpr auto suffix = "]";
    constexpr auto function = std::string_view{__PRETTY_FUNCTION__};
#elif defined(__GNUC__)
    constexpr auto prefix = std::string_view{"with T = "};
    constexpr auto suffix = "; ";
    constexpr auto function = std::string_view{__PRETTY_FUNCTION__};
#elif defined(_MSC_VER)
    constexpr auto prefix = std::string_view{"get_type_name<"};
    constexpr auto suffix = ">(void)";
    constexpr auto function = std::string_view{__FUNCSIG__};
#else
# error Unsupported compiler (although this code only beautifies the output!)
#endif

    const auto start = function.find(prefix) + prefix.size();
    const auto end = function.find(suffix);
    const auto size = end - start;

    return function.substr(start, size);
}

#endif // !CIARCPP_PARSE_GETTYPENAME_HPP