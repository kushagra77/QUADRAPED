// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from quadruped_interfaces:msg/Pos.idl
// generated code does not contain a copyright notice

#include "quadruped_interfaces/msg/detail/pos__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_quadruped_interfaces
const rosidl_type_hash_t *
quadruped_interfaces__msg__Pos__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x4d, 0xbb, 0xdd, 0x29, 0xbd, 0x18, 0x73, 0x17,
      0x88, 0x19, 0x96, 0xdc, 0x4d, 0x31, 0x03, 0xd3,
      0x35, 0xb4, 0xb9, 0x59, 0x97, 0xd1, 0x68, 0xa8,
      0x9d, 0xcc, 0xe2, 0x52, 0x6c, 0x9b, 0x05, 0x1c,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char quadruped_interfaces__msg__Pos__TYPE_NAME[] = "quadruped_interfaces/msg/Pos";

// Define type names, field names, and default values
static char quadruped_interfaces__msg__Pos__FIELD_NAME__x[] = "x";
static char quadruped_interfaces__msg__Pos__FIELD_NAME__z[] = "z";

static rosidl_runtime_c__type_description__Field quadruped_interfaces__msg__Pos__FIELDS[] = {
  {
    {quadruped_interfaces__msg__Pos__FIELD_NAME__x, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {quadruped_interfaces__msg__Pos__FIELD_NAME__z, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
quadruped_interfaces__msg__Pos__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {quadruped_interfaces__msg__Pos__TYPE_NAME, 28, 28},
      {quadruped_interfaces__msg__Pos__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float64 x\n"
  "float64 z";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
quadruped_interfaces__msg__Pos__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {quadruped_interfaces__msg__Pos__TYPE_NAME, 28, 28},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 19, 19},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
quadruped_interfaces__msg__Pos__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *quadruped_interfaces__msg__Pos__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
