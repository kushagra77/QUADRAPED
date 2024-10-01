// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from quadruped_interfaces:msg/Pos.idl
// generated code does not contain a copyright notice

#ifndef QUADRUPED_INTERFACES__MSG__DETAIL__POS__BUILDER_HPP_
#define QUADRUPED_INTERFACES__MSG__DETAIL__POS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "quadruped_interfaces/msg/detail/pos__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace quadruped_interfaces
{

namespace msg
{

namespace builder
{

class Init_Pos_z
{
public:
  explicit Init_Pos_z(::quadruped_interfaces::msg::Pos & msg)
  : msg_(msg)
  {}
  ::quadruped_interfaces::msg::Pos z(::quadruped_interfaces::msg::Pos::_z_type arg)
  {
    msg_.z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::quadruped_interfaces::msg::Pos msg_;
};

class Init_Pos_x
{
public:
  Init_Pos_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Pos_z x(::quadruped_interfaces::msg::Pos::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Pos_z(msg_);
  }

private:
  ::quadruped_interfaces::msg::Pos msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::quadruped_interfaces::msg::Pos>()
{
  return quadruped_interfaces::msg::builder::Init_Pos_x();
}

}  // namespace quadruped_interfaces

#endif  // QUADRUPED_INTERFACES__MSG__DETAIL__POS__BUILDER_HPP_
