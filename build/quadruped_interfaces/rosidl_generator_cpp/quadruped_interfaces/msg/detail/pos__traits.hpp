// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from quadruped_interfaces:msg/Pos.idl
// generated code does not contain a copyright notice

#ifndef QUADRUPED_INTERFACES__MSG__DETAIL__POS__TRAITS_HPP_
#define QUADRUPED_INTERFACES__MSG__DETAIL__POS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "quadruped_interfaces/msg/detail/pos__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace quadruped_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Pos & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: z
  {
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Pos & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Pos & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace quadruped_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use quadruped_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const quadruped_interfaces::msg::Pos & msg,
  std::ostream & out, size_t indentation = 0)
{
  quadruped_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use quadruped_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const quadruped_interfaces::msg::Pos & msg)
{
  return quadruped_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<quadruped_interfaces::msg::Pos>()
{
  return "quadruped_interfaces::msg::Pos";
}

template<>
inline const char * name<quadruped_interfaces::msg::Pos>()
{
  return "quadruped_interfaces/msg/Pos";
}

template<>
struct has_fixed_size<quadruped_interfaces::msg::Pos>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<quadruped_interfaces::msg::Pos>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<quadruped_interfaces::msg::Pos>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // QUADRUPED_INTERFACES__MSG__DETAIL__POS__TRAITS_HPP_
