# Additional CMake macros
#
# Copyright (C) 2015-2016 Jarosław Staniek <staniek@kde.org>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

include(KDbGenerateHeaders) # from KDb, adds support for generated headers to ECMGenerateHeaders
include(KDbCreateSharedDataClasses) # from KDb
include(GenerateExportHeader)
include(MacroLogFeature)
include(FeatureSummary)
include(GetGitRevisionDescription)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)
string(COMPARE EQUAL "${CMAKE_CXX_COMPILER_ID}" "Clang" CMAKE_COMPILER_IS_CLANG)

# x.80.y or larger means test release, so the stable major version is x+1
if(PROJECT_VERSION_MINOR GREATER 80)
    set(PROJECT_UNSTABLE ON)
    math(EXPR PROJECT_STABLE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR} + 1")
else()
    set(PROJECT_STABLE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
endif()

if(WIN32)
    set(LIB_INSTALL_DIR ${LIB_INSTALL_DIR}
                        RUNTIME DESTINATION ${BIN_INSTALL_DIR}
                        LIBRARY ${INSTALL_TARGETS_DEFAULT_ARGS}
                        ARCHIVE ${INSTALL_TARGETS_DEFAULT_ARGS} )
    set(DATA_INSTALL_DIR "$ENV{APPDATA}")
    STRING(REGEX REPLACE "\\\\" "/" DATA_INSTALL_DIR ${DATA_INSTALL_DIR})
    # Install own icons to CMAKE_INSTALL_FULL_ICONDIR (relative to bin/data/ on Windows) on Windows.
    # We're consistent because icons from breeze-icons.git are installed there as well.
    set(ICONS_INSTALL_DIR ${CMAKE_INSTALL_FULL_ICONDIR})
else()
    # On other OSes install own icons in app's data dir
    set(ICONS_INSTALL_DIR
        "${DATA_INSTALL_DIR}/${PROJECT_NAME_LOWER}${PROJECT_STABLE_VERSION_MAJOR}/icons")
endif()

# Adds a feature info using add_feature_info() with _NAME and _DESCRIPTION.
# If _NAME is equal to _DEFAULT, shows this fact.
macro(add_simple_feature_info _NAME _DESCRIPTION _DEFAULT)
  if("${_DEFAULT}" STREQUAL "${${_NAME}}")
    set(_STATUS " (default value)")
  else()
    set(_STATUS "")
  endif()
  add_feature_info(${_NAME} ${_NAME} ${_DESCRIPTION}${_STATUS})
endmacro()

# Adds a simple option using option() with _NAME and _DESCRIPTION and a feature
# info for it using add_simple_feature_info(). If _NAME is equal to _DEFAULT, shows this fact.
macro(simple_option _NAME _DESCRIPTION _DEFAULT)
  option(${_NAME} ${_DESCRIPTION} ${_DEFAULT})
  add_simple_feature_info(${_NAME} ${_DESCRIPTION} ${_DEFAULT})
endmacro()

# Fetches git revision and branch from the source dir of the current build if possible.
# Sets ${PROJECT_NAME_UPPER}_GIT_SHA1_STRING and ${PROJECT_NAME_UPPER}_GIT_BRANCH_STRING variables.
# If git information is not available but ${CMAKE_SOURCE_DIR}/GIT_VERSION file exists,
# it is parsed. This file can be created by scripts while preparing tarballs and is
# supposed to contain two lines: hash and branch.
macro(get_git_revision_and_branch)
  set(${PROJECT_NAME_UPPER}_GIT_SHA1_STRING "")
  set(${PROJECT_NAME_UPPER}_GIT_BRANCH_STRING "")
  get_git_head_revision(GIT_REFSPEC ${PROJECT_NAME_UPPER}_GIT_SHA1_STRING)
  get_git_branch(${PROJECT_NAME_UPPER}_GIT_BRANCH_STRING)
  if(NOT ${PROJECT_NAME_UPPER}_GIT_SHA1_STRING OR NOT ${PROJECT_NAME_UPPER}_GIT_BRANCH_STRING)
    if(EXISTS "${CMAKE_SOURCE_DIR}/GIT_VERSION")
      file(READ "${CMAKE_SOURCE_DIR}/GIT_VERSION" _ver)
      string(REGEX REPLACE "\n" ";" _ver "${_ver}")
      list(GET _ver 0 ${PROJECT_NAME_UPPER}_GIT_SHA1_STRING)
      list(GET _ver 1 ${PROJECT_NAME_UPPER}_GIT_BRANCH_STRING)
    endif()
  endif()
  if(${PROJECT_NAME_UPPER}_GIT_SHA1_STRING OR ${PROJECT_NAME_UPPER}_GIT_BRANCH_STRING)
    string(SUBSTRING ${${PROJECT_NAME_UPPER}_GIT_SHA1_STRING} 0 7 ${PROJECT_NAME_UPPER}_GIT_SHA1_STRING)
  else()
    set(${PROJECT_NAME_UPPER}_GIT_SHA1_STRING "")
    set(${PROJECT_NAME_UPPER}_GIT_BRANCH_STRING "")
  endif()
endmacro()

# Adds BUILD_TESTING option to enable all kinds of tests. If enabled, build in autotests/
# and tests/ subdirectory is enabled. IF optional argument ARG1 is ON, building tests will
# be ON by default. Otherwise building tests will be OFF. ARG1 is OFF by default.
# If tests are OFF, BUILD_COVERAGE is set to OFF.
# If tests are on BUILD_TESTING macro is defined.
macro(add_tests)
  if (NOT "${ARG1}" STREQUAL "ON")
    set(_SET OFF)
  endif()
  simple_option(BUILD_TESTING "Build tests" ${_SET}) # override default from CTest.cmake
  if(BUILD_TESTING)
    add_definitions(-DBUILD_TESTING)
    include(CTest)
    if (EXISTS ${CMAKE_SOURCE_DIR}/autotests)
        add_subdirectory(autotests)
    endif()
    if (EXISTS ${CMAKE_SOURCE_DIR}/tests)
        add_subdirectory(tests)
    endif()
  else()
    set(BUILD_COVERAGE OFF)
    simple_option(BUILD_COVERAGE "Build test coverage (disabled because BUILD_TESTING is OFF)" OFF)
  endif()
endmacro()

# Adds BUILD_EXAMPLES option to enable examples. If enabled, build in examples/ subdirectory
# is enabled. If optional argument ARG1 is ON, building examples will be ON by default.
# Otherwise building examples will be OFF. ARG1 is OFF by default.
macro(add_examples)
  set(_SET ${ARGV0})
  if (NOT "${_SET}" STREQUAL ON)
    set(_SET OFF)
  endif()
  simple_option(BUILD_EXAMPLES "Build example applications" ${_SET})
  if (BUILD_EXAMPLES AND EXISTS ${CMAKE_SOURCE_DIR}/examples)
    add_subdirectory(examples)
  endif()
endmacro()

# Adds ${PROJECT_NAME_UPPER}_UNFINISHED option. If it is ON, unfinished features
# (useful for testing but may confuse end-user) are compiled-in.
# This option is OFF by default.
macro(add_unfinished_features_option)
  simple_option(${PROJECT_NAME_UPPER}_UNFINISHED
                "Include unfinished features (useful for testing but may confuse end-user)" OFF)
endmacro()

# Adds commands that generate ${_filename}${PROJECT_STABLE_VERSION_MAJOR}.pc file
# out of ${_filename}.pc.cmake file and installs the .pc file to ${LIB_INSTALL_DIR}/pkgconfig.
# These commands are not executed for WIN32.
# ${CMAKE_SOURCE_DIR}/${_filename}.pc.cmake should exist.
macro(add_pc_file _filename)
  if (NOT WIN32)
    set(_name ${_filename}${PROJECT_STABLE_VERSION_MAJOR})
    configure_file(${CMAKE_SOURCE_DIR}/${_filename}.pc.cmake ${CMAKE_BINARY_DIR}/${_name}.pc @ONLY)
    install(FILES ${CMAKE_BINARY_DIR}/${_name}.pc DESTINATION ${LIB_INSTALL_DIR}/pkgconfig)
  endif()
endmacro()

# Sets detailed version information for library co-installability.
# - adds PROJECT_VERSION_MAJOR to the lib name
# - sets VERSION and SOVERSION to PROJECT_VERSION_MAJOR.PROJECT_VERSION_MINOR
# - sets ${_target_upper}_BASE_NAME variable to the final lib name
# - sets ${_target_upper}_BASE_NAME_LOWER variable to the final lib name, lowercase
# - sets ${_target_upper}_INCLUDE_INSTALL_DIR to include dir for library headers
# - (where _target_upper is uppercase ${_target}
macro(set_coinstallable_lib_version _target)
    set(_name ${_target}${PROJECT_STABLE_VERSION_MAJOR})
    set_target_properties(${_target}
        PROPERTIES VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
                   SOVERSION ${PROJECT_VERSION_MAJOR}
                   EXPORT_NAME ${_target}
                   OUTPUT_NAME ${_name}
    )
    string(TOUPPER ${_target} _target_upper)
    string(TOUPPER ${_target_upper}_BASE_NAME _var)
    set(${_var} ${_name})
    string(TOLOWER ${_name} ${_var}_LOWER)
    set(${_target_upper}_INCLUDE_INSTALL_DIR ${INCLUDE_INSTALL_DIR}/${_name})
    unset(_target_upper)
    unset(_var)
endmacro()

# Adds custom target ${_target} that updates file ${_file} in the current working dir
# using command ${_command} and add sources ${_sources} to the project files.
# The command is run as a part of the project.
function(add_update_file_target)
    set(options)
    set(oneValueArgs TARGET FILE)
    set(multiValueArgs COMMAND SOURCES)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    add_custom_target(${ARG_TARGET}
        COMMAND ${ARG_COMMAND}
        SOURCES ${ARG_SOURCES}
        DEPENDS ${ARG_SOURCES}
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Updating ${ARG_FILE}"
        VERBATIM
    )
endfunction()
