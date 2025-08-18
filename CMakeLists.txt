cmake_minimum_required(VERSION 3.12)

# Set policy to use new Boost finding mechanism
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter_project VERSION ${PROJECT_VERSION})

option(WITH_GTEST "Whether to build Google-test" ON)

configure_file(src/version.h.in version.h)

#***********************************************************************************#
#************************************ G-TESTS **************************************#
#***********************************************************************************#

if(WITH_GTEST)
    #download googletest sources at configure time to build directory
    #build from sources at build time
    include(FetchContent)
    #describe how to get content
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            #it is advisable to use a hash for GIT_TAG rather than a branch or tag name.
            #A commit hash is more secure and helps to confirm that the downloaded contents are what you expected.
            GIT_TAG        6910c9d   # release-1.16.0
    )
    #make sure that all the dependencies are available
    FetchContent_MakeAvailable(googletest)

    #no add_subdirectory to googletest requires!

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

#***********************************************************************************#
#************************************ G-TESTS **************************************#
#***********************************************************************************#

# Create ip_filter_lib for shared code
add_library(
        ip_filter_lib
        src/ip_filter_lib.cpp
)

add_executable(
        ip_filter
        src/ip_filter.cpp
)

add_library(
        version_lib
        src/version_lib.cpp
)

set_target_properties(ip_filter ip_filter_lib version_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(version_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_include_directories(ip_filter_lib
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
    version_lib
)

# Set compiler warning flags for ip_filter
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(ip_filter PRIVATE /W4 /WX)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(ip_filter PRIVATE -Wall -Wextra -pedantic -Werror)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    target_compile_options(ip_filter PRIVATE -Wall -Wextra -pedantic -Werror)
else()
    message(WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}. No specific warning flags set.")
endif()

if(WITH_GTEST)
    # Test target
    add_executable(
            google_test_list
            google_tests/test_list.cpp
            google_tests/tests.cpp
    )

    # Add src to the include directories for the test target
    target_include_directories(
            google_test_list PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/src"
    )

    # Link test target against gtest libraries
    target_link_libraries(
            google_test_list PRIVATE
            gtest
            ip_filter_lib
            version_lib
    )

    set_target_properties(google_test_list PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

    # Set compiler warning flags based on compiler identification
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(google_test_list PRIVATE /W4 /WX)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(google_test_list PRIVATE -Wall -Wextra -pedantic -Werror)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
        target_compile_options(google_test_list PRIVATE -Wall -Wextra -pedantic -Werror)
    else()
        message(WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}. No specific warning flags set.")
    endif()
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME "ip_filter")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
