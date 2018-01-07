#pragma once

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>
#include <string>

namespace details
{
/*! \brief specialize a type for all sequence STL containers.
 */
template <typename T> struct is_stl_sequence_container:std::false_type{};
template <typename T, std::size_t N> struct is_stl_sequence_container<std::array<T,N>>    :std::true_type{};
template <typename... Args> struct is_stl_sequence_container<std::vector        <Args...>>:std::true_type{};
template <typename... Args> struct is_stl_sequence_container<std::deque         <Args...>>:std::true_type{};
template <typename... Args> struct is_stl_sequence_container<std::list          <Args...>>:std::true_type{};
template <typename... Args> struct is_stl_sequence_container<std::forward_list  <Args...>>:std::true_type{};

/*! \brief specialize a type for std::string.
 */
template <typename T> struct is_stl_string:std::false_type{};
template <> struct is_stl_string<std::string>:std::true_type{};

/*! \brief specialize a type for char and unsigned char.
 */
template <typename T> struct is_char:std::false_type{};
template <> struct is_char<char>:std::true_type{};
template <> struct is_char<unsigned char>:std::true_type{};
}

/*! \brief type trait to utilize the implementation type traits as well as decay the type
 */
template <typename T> struct is_stl_sequence_container
{
    static constexpr bool const value = details::is_stl_sequence_container<std::decay_t<T>>::value;
};

template <typename T> struct is_stl_string
{
    static constexpr bool const value = details::is_stl_string<std::decay_t<T>>::value;
};

template <typename T> struct is_char
{
    static constexpr bool const value = details::is_char<std::decay_t<T>>::value;
};
