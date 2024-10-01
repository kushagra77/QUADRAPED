#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "quadruped_interfaces::quadruped_interfaces__rosidl_generator_py" for configuration ""
set_property(TARGET quadruped_interfaces::quadruped_interfaces__rosidl_generator_py APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(quadruped_interfaces::quadruped_interfaces__rosidl_generator_py PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libquadruped_interfaces__rosidl_generator_py.so"
  IMPORTED_SONAME_NOCONFIG "libquadruped_interfaces__rosidl_generator_py.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS quadruped_interfaces::quadruped_interfaces__rosidl_generator_py )
list(APPEND _IMPORT_CHECK_FILES_FOR_quadruped_interfaces::quadruped_interfaces__rosidl_generator_py "${_IMPORT_PREFIX}/lib/libquadruped_interfaces__rosidl_generator_py.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
