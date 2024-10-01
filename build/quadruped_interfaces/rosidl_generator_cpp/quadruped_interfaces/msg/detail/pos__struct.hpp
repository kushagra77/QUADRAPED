// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from quadruped_interfaces:msg/Pos.idl
// generated code does not contain a copyright notice

#ifndef QUADRUPED_INTERFACES__MSG__DETAIL__POS__STRUCT_HPP_
#define QUADRUPED_INTERFACES__MSG__DETAIL__POS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__quadruped_interfaces__msg__Pos __attribute__((deprecated))
#else
# define DEPRECATED__quadruped_interfaces__msg__Pos __declspec(deprecated)
#endif

namespace quadruped_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Pos_
{
  using Type = Pos_<ContainerAllocator>;

  explicit Pos_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0;
      this->z = 0.0;
    }
  }

  explicit Pos_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0;
      this->z = 0.0;
    }
  }

  // field types and members
  using _x_type =
    double;
  _x_type x;
  using _z_type =
    double;
  _z_type z;

  // setters for named parameter idiom
  Type & set__x(
    const double & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__z(
    const double & _arg)
  {
    this->z = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    quadruped_interfaces::msg::Pos_<ContainerAllocator> *;
  using ConstRawPtr =
    const quadruped_interfaces::msg::Pos_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<quadruped_interfaces::msg::Pos_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<quadruped_interfaces::msg::Pos_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      quadruped_interfaces::msg::Pos_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<quadruped_interfaces::msg::Pos_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      quadruped_interfaces::msg::Pos_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<quadruped_interfaces::msg::Pos_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<quadruped_interfaces::msg::Pos_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<quadruped_interfaces::msg::Pos_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__quadruped_interfaces__msg__Pos
    std::shared_ptr<quadruped_interfaces::msg::Pos_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__quadruped_interfaces__msg__Pos
    std::shared_ptr<quadruped_interfaces::msg::Pos_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Pos_ & other) const
  {
    if (this->x != other.x) {
      return false;
    }
    if (this->z != other.z) {
      return false;
    }
    return true;
  }
  bool operator!=(const Pos_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Pos_

// alias to use template instance with default allocator
using Pos =
  quadruped_interfaces::msg::Pos_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace quadruped_interfaces

#endif  // QUADRUPED_INTERFACES__MSG__DETAIL__POS__STRUCT_HPP_
