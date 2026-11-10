cmake_minimum_required(VERSION 3.15)
project(libgoogle VERSION 4.2 LANGUAGES C CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
 
if(NOT MSVC)
    message(FATAL_ERROR "libgoogle requiere arquitectura Win y compilador MSVC.")
endif()
 
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PLATFORM_DIR "x32")
else()
    set(PLATFORM_DIR "x64")
endif()

set(ARQUITECTURE_DIR ${CMAKE_SYSTEM_PROCESSOR})
if(NOT ARQUITECTURE_DIR)
    set(ARQUITECTURE_DIR ${CMAKE_HOST_SYSTEM_NAME})
endif()

set(DIR_BUILD "${PLATFORM_DIR}-${ARQUITECTURE_DIR}")


set(CORESDK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/core-c-sdk)
set(LIBSTRING_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libstring)
set(LIBIO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libio)
set(LIBCRYPTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libcrypto)
set(LIBWREQ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libwreq) 
set(LIBHTML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libhtml) 

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "No buscar actualizaciones en GitHub si ya existe")

FetchContent_Declare(
  coresdk
  GIT_REPOSITORY https://github.com/christian-gutman/core-c-sdk
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${CORESDK_DIR}
)
FetchContent_MakeAvailable(coresdk)

FetchContent_Declare(
  libstring
  GIT_REPOSITORY https://github.com/christian-gutman/libstring.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBSTRING_DIR}
)
FetchContent_MakeAvailable(libstring)
 
FetchContent_Declare(
  libcrypto
  GIT_REPOSITORY https://github.com/christian-gutman/libcrypto.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBCRYPTO_DIR}
)
FetchContent_MakeAvailable(libcrypto)

FetchContent_Declare(
  libio
  GIT_REPOSITORY https://github.com/christian-gutman/libio.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBIO_DIR}
)
FetchContent_MakeAvailable(libio)

FetchContent_Declare(
  libwreq
  GIT_REPOSITORY https://github.com/christian-gutman/libwreq.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBWREQ_DIR}
)
FetchContent_MakeAvailable(libwreq)


FetchContent_Declare(
  libhtml
  GIT_REPOSITORY https://github.com/christian-gutman/libhtml.git
  GIT_TAG        v2.6.0.0
  SOURCE_DIR     ${LIBHTML_DIR}
)
FetchContent_MakeAvailable(libhtml)

set(SRC_libgoogle
    "${CORESDK_DIR}/src/core/core.h"   
    "${CORESDK_DIR}/src/core/core.c"  

    "${LIBSTRING_DIR}/src/strings/core/core_encoding.h"    
    "${LIBSTRING_DIR}/src/strings/core/core_encoding.c"    

    "${LIBSTRING_DIR}/src/strings/core/core_string.h"    
    "${LIBSTRING_DIR}/src/strings/core/core_string.c" 

    "${LIBIO_DIR}/src/io/core/core_io.h"    
    "${LIBIO_DIR}/src/io/core/core_io.c" 
    
    "${LIBCRYPTO_DIR}/src/crypto/core/core_crypto.h"    
    "${LIBCRYPTO_DIR}/src/crypto/core/core_crypto.c" 

    "${LIBWREQ_DIR}/src/request/core/core_request.h"    
    "${LIBWREQ_DIR}/src/request/core/core_request.c" 

    "${LIBWREQ_DIR}/src/request/core/core_req_file.h"    
    "${LIBWREQ_DIR}/src/request/core/core_req_file.c" 

    "${LIBWREQ_DIR}/src/request/core/core_rest.h"    
    "${LIBWREQ_DIR}/src/request/core/core_rest.c" 

    "${LIBHTML_DIR}/src/html/core/core_html.h"    
    "${LIBHTML_DIR}/src/html/core/core_html.c" 

    "${CMAKE_CURRENT_SOURCE_DIR}/core/google.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/core/google_geopos.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/core/google_geopos.c"
    #
    "${CMAKE_CURRENT_SOURCE_DIR}/core/google.rc"
)
 
add_library(libgoogle SHARED ${SRC_libgoogle})

target_include_directories(libgoogle PRIVATE
    "${CORESDK_DIR}/src/core"                             # Para resolver rutas relativas del SDK
    "${LIBSTRING_DIR}/src/strings/core"  
    "${LIBIO_DIR}/src/io/core"  
    "${LIBCRYPTO_DIR}/src/crypto/core"
    "${LIBWREQ_DIR}/src/request/core"
    "${LIBHTML_DIR}/src/html/core"     
) 


set_target_properties(libgoogle PROPERTIES LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/core/google.def")
 
set_target_properties(libgoogle PROPERTIES
    PREFIX ""
    OUTPUT_NAME "libgoogle"
    SUFFIX ".dll"
    WINDOWS_EXPORT_ALL_SYMBOLS FALSE 
) 

target_compile_definitions(libgoogle PRIVATE
    WIN32 _WINDOWS _USRDLL UNICODE _UNICODE _CRT_SECURE_NO_WARNINGS TARGET_OS_WIN32 WIN32_LEAN_AND_MEAN _WINSOCK_DEPRECATED_NO_WARNINGS
) 


target_link_libraries(libgoogle PRIVATE winhttp crypt32 bcrypt ncrypt ${VFP_LIB})

set(DIR_BIN "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/${DIR_BUILD}")

set_target_properties(libgoogle PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${DIR_BIN}/$<CONFIG>"
    LIBRARY_OUTPUT_DIRECTORY "${DIR_BIN}/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY "${DIR_BIN}/$<CONFIG>"
)
  
