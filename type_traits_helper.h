#pragma once

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>
#include <string>
#include <type_traits>

namespace detail
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

///*! \brief C++17 compatibility
// */
//template <class T, class Tuple, std::size_t... I>
//constexpr T make_from_tuple_impl(Tuple&& t, std::index_sequence<I...>)
//{
//  return T(std::get<I>(std::forward<Tuple>(t))...);
//}

} // namespace detail


/*! \brief C++14 compatibility
 */
template<class T>
using decay_t = typename std::decay<T>::type;

template<bool B, class T = void>
using enable_if_t = typename std::enable_if<B,T>::type;


///*! \brief C++17 compatibility
// */
//template <class T, class Tuple>
//constexpr T make_from_tuple(Tuple&& t)
//{
//    return detail::make_from_tuple_impl<T>(std::forward<Tuple>(t),
//        std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value>{});
//}

/*! \brief type trait to utilize the implementation type traits as well as decay the type
 */
template <typename T> struct is_stl_sequence_container
{
    static constexpr bool const value = detail::is_stl_sequence_container<decay_t<T>>::value;
};

template <typename T> struct is_stl_string
{
    static constexpr bool const value = detail::is_stl_string<decay_t<T>>::value;
};

template <typename T> struct is_char
{
    static constexpr bool const value = detail::is_char<decay_t<T>>::value;
};
