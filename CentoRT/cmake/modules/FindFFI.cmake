if(NOT FFI_ROOT)
  set(_FFI_HINTS
    "C:/msys64/mingw64"
    "C:/msys64/ucrt64"
    "C:/Program Files/libffi"
    "C:/libffi"
  )
else()
  set(_FFI_HINTS "${FFI_ROOT}")
endif()

find_path(FFI_INCLUDE_DIR
  NAMES ffi.h
  HINTS ${_FFI_HINTS}
  PATH_SUFFIXES include libffi include/libffi
)

if(MSVC)
  find_library(FFI_LIBRARY
    NAMES ffi libffi libffi-8
    HINTS ${_FFI_HINTS}
    PATH_SUFFIXES lib lib64)
else()
  find_library(FFI_LIBRARY
    NAMES ffi libffi libffi-8
    HINTS ${_FFI_HINTS}
    PATH_SUFFIXES lib lib64)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FFI
  REQUIRED_VARS FFI_INCLUDE_DIR FFI_LIBRARY
  FAIL_MESSAGE "libffi not found. Set FFI_ROOT or FFI_INCLUDE_DIR/FFI_LIBRARY."
)

set(FFI_INCLUDE_DIRS ${FFI_INCLUDE_DIR})
set(FFI_LIBRARIES    ${FFI_LIBRARY})

mark_as_advanced(FFI_INCLUDE_DIR FFI_LIBRARY)
