// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from quadruped_interfaces:msg/Pos.idl
// generated code does not contain a copyright notice
#include "quadruped_interfaces/msg/detail/pos__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
quadruped_interfaces__msg__Pos__init(quadruped_interfaces__msg__Pos * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // z
  return true;
}

void
quadruped_interfaces__msg__Pos__fini(quadruped_interfaces__msg__Pos * msg)
{
  if (!msg) {
    return;
  }
  // x
  // z
}

bool
quadruped_interfaces__msg__Pos__are_equal(const quadruped_interfaces__msg__Pos * lhs, const quadruped_interfaces__msg__Pos * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // z
  if (lhs->z != rhs->z) {
    return false;
  }
  return true;
}

bool
quadruped_interfaces__msg__Pos__copy(
  const quadruped_interfaces__msg__Pos * input,
  quadruped_interfaces__msg__Pos * output)
{
  if (!input || !output) {
    return false;
  }
  // x
  output->x = input->x;
  // z
  output->z = input->z;
  return true;
}

quadruped_interfaces__msg__Pos *
quadruped_interfaces__msg__Pos__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  quadruped_interfaces__msg__Pos * msg = (quadruped_interfaces__msg__Pos *)allocator.allocate(sizeof(quadruped_interfaces__msg__Pos), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(quadruped_interfaces__msg__Pos));
  bool success = quadruped_interfaces__msg__Pos__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
quadruped_interfaces__msg__Pos__destroy(quadruped_interfaces__msg__Pos * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    quadruped_interfaces__msg__Pos__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
quadruped_interfaces__msg__Pos__Sequence__init(quadruped_interfaces__msg__Pos__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  quadruped_interfaces__msg__Pos * data = NULL;

  if (size) {
    data = (quadruped_interfaces__msg__Pos *)allocator.zero_allocate(size, sizeof(quadruped_interfaces__msg__Pos), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = quadruped_interfaces__msg__Pos__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        quadruped_interfaces__msg__Pos__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
quadruped_interfaces__msg__Pos__Sequence__fini(quadruped_interfaces__msg__Pos__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      quadruped_interfaces__msg__Pos__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

quadruped_interfaces__msg__Pos__Sequence *
quadruped_interfaces__msg__Pos__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  quadruped_interfaces__msg__Pos__Sequence * array = (quadruped_interfaces__msg__Pos__Sequence *)allocator.allocate(sizeof(quadruped_interfaces__msg__Pos__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = quadruped_interfaces__msg__Pos__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
quadruped_interfaces__msg__Pos__Sequence__destroy(quadruped_interfaces__msg__Pos__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    quadruped_interfaces__msg__Pos__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
quadruped_interfaces__msg__Pos__Sequence__are_equal(const quadruped_interfaces__msg__Pos__Sequence * lhs, const quadruped_interfaces__msg__Pos__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!quadruped_interfaces__msg__Pos__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
quadruped_interfaces__msg__Pos__Sequence__copy(
  const quadruped_interfaces__msg__Pos__Sequence * input,
  quadruped_interfaces__msg__Pos__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(quadruped_interfaces__msg__Pos);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    quadruped_interfaces__msg__Pos * data =
      (quadruped_interfaces__msg__Pos *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!quadruped_interfaces__msg__Pos__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          quadruped_interfaces__msg__Pos__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!quadruped_interfaces__msg__Pos__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
