// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from quadruped_interfaces:msg/Pos.idl
// generated code does not contain a copyright notice

#ifndef QUADRUPED_INTERFACES__MSG__DETAIL__POS__STRUCT_H_
#define QUADRUPED_INTERFACES__MSG__DETAIL__POS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Pos in the package quadruped_interfaces.
typedef struct quadruped_interfaces__msg__Pos
{
  double x;
  double z;
} quadruped_interfaces__msg__Pos;

// Struct for a sequence of quadruped_interfaces__msg__Pos.
typedef struct quadruped_interfaces__msg__Pos__Sequence
{
  quadruped_interfaces__msg__Pos * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} quadruped_interfaces__msg__Pos__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // QUADRUPED_INTERFACES__MSG__DETAIL__POS__STRUCT_H_
