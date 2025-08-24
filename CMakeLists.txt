cmake_minimum_required(VERSION 3.12)

# Set policy to use new Boost finding mechanism
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(cpp_prof_2025_project VERSION ${PROJECT_VERSION})

# Apply warning flags globally without generator expressions (works with CLion's probe)
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /WX)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -pedantic -Werror)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

option(WITH_GTEST "Whether to build Google-test" ON)

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

add_executable(
        00_problem
        src/00_problem.cpp
)

add_executable(
        01_basic_case
        src/01_basic_case.cpp
        src/01_simple_smart_ptr.h
)


add_executable(
        02_basic_case
        src/02_basic_case.cpp
        src/02_simple_shared_ptr.h
)

add_executable(
        03_minimal_weak_main
        src/03_minimal_weak_main.cpp
        src/03_minimal_weak_ptr.h
)

set_target_properties(
        00_problem
        01_basic_case
        02_basic_case
        03_minimal_weak_main
        PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

#***********************************************************************************#
#************************************ G-TESTS **************************************#
#***********************************************************************************#

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

# Install the actual executables you define here.
# NOTE: Do not reference a non-existent target like 'ip_filter'.
install(TARGETS
    00_problem
    01_basic_case
    02_basic_case
    03_minimal_weak_main
    RUNTIME DESTINATION bin
)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME "ip_filter")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
