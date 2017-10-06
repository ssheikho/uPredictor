# Install script for directory: D:/upredictor/uPredictor/ThirdParty/ceres-solver

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/Ceres")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ceres" TYPE FILE FILES
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/autodiff_cost_function.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/autodiff_local_parameterization.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/ceres.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/conditioned_cost_function.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/cost_function.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/cost_function_to_functor.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/covariance.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/crs_matrix.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/cubic_interpolation.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/c_api.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/dynamic_autodiff_cost_function.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/dynamic_cost_function_to_functor.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/dynamic_numeric_diff_cost_function.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/fpclassify.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/gradient_checker.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/gradient_problem.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/gradient_problem_solver.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/iteration_callback.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/jet.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/local_parameterization.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/loss_function.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/normal_prior.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/numeric_diff_cost_function.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/numeric_diff_options.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/ordered_groups.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/problem.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/rotation.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/sized_cost_function.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/solver.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/types.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/version.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ceres/internal" TYPE FILE FILES
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/internal/autodiff.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/internal/disable_warnings.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/internal/eigen.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/internal/fixed_array.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/internal/macros.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/internal/manual_constructor.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/internal/numeric_diff.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/internal/port.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/internal/reenable_warnings.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/internal/scoped_ptr.h"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/include/ceres/internal/variadic_evaluate.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ceres/internal" TYPE FILE FILES "D:/upredictor/uPredictor/ThirdParty/CERES/config/ceres/internal/config.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/CMake/CeresTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/CMake/CeresTargets.cmake"
         "D:/upredictor/uPredictor/ThirdParty/CERES/CMakeFiles/Export/CMake/CeresTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/CMake/CeresTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/CMake/CeresTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/CMake" TYPE FILE FILES "D:/upredictor/uPredictor/ThirdParty/CERES/CMakeFiles/Export/CMake/CeresTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/CMake" TYPE FILE FILES "D:/upredictor/uPredictor/ThirdParty/CERES/CMakeFiles/Export/CMake/CeresTargets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/CMake" TYPE FILE FILES "D:/upredictor/uPredictor/ThirdParty/CERES/CMakeFiles/Export/CMake/CeresTargets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/CMake" TYPE FILE FILES "D:/upredictor/uPredictor/ThirdParty/CERES/CMakeFiles/Export/CMake/CeresTargets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/CMake" TYPE FILE FILES "D:/upredictor/uPredictor/ThirdParty/CERES/CMakeFiles/Export/CMake/CeresTargets-release.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/CMake" TYPE FILE RENAME "CeresConfig.cmake" FILES "D:/upredictor/uPredictor/ThirdParty/CERES/CeresConfig-install.cmake")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/CMake" TYPE FILE FILES
    "D:/upredictor/uPredictor/ThirdParty/CERES/CeresConfigVersion.cmake"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/cmake/FindEigen.cmake"
    "D:/upredictor/uPredictor/ThirdParty/ceres-solver/cmake/FindGlog.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/upredictor/uPredictor/ThirdParty/CERES/internal/ceres/cmake_install.cmake")
  include("D:/upredictor/uPredictor/ThirdParty/CERES/examples/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/upredictor/uPredictor/ThirdParty/CERES/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
