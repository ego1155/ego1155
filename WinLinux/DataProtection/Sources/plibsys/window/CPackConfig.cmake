# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_7Z "OFF")
set(CPACK_BINARY_IFW "OFF")
set(CPACK_BINARY_NSIS "ON")
set(CPACK_BINARY_NUGET "OFF")
set(CPACK_BINARY_WIX "OFF")
set(CPACK_BINARY_ZIP "OFF")
set(CPACK_BUILD_SOURCE_DIRS "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/plibsys;C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window")
set(CPACK_CMAKE_GENERATOR "MSYS Makefiles")
set(CPACK_COMPONENTS_ALL "Core")
set(CPACK_COMPONENTS_ALL_SET_BY_USER "TRUE")
set(CPACK_COMPONENT_CORE_DESCRIPTION "Core library with headers")
set(CPACK_COMPONENT_CORE_DISPLAY_NAME "Core components")
set(CPACK_COMPONENT_CORE_REQUIRED "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "C:/msys64/mingw64/share/cmake-3.21/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "plibsys built using CMake")
set(CPACK_GENERATOR "NSIS")
set(CPACK_INSTALL_CMAKE_PROJECTS "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window;plibsys;ALL;/")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/plibsys")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "plibsys")
set(CPACK_NSIS_DISPLAY_NAME_SET "TRUE")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_PACKAGE_NAME "plibsys")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "C:/msys64/mingw64/share/cmake-3.21/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "plibsys - System routines library")
set(CPACK_PACKAGE_FILE_NAME "plibsys-installer-0.0.4-win64")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "plibsys-0.0.4")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "plibsys-0.0.4")
set(CPACK_PACKAGE_NAME "plibsys-installer")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Alexander Saprykin")
set(CPACK_PACKAGE_VERSION "0.0.4")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "4")
set(CPACK_RESOURCE_FILE_LICENSE "C:/msys64/mingw64/share/cmake-3.21/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "C:/msys64/mingw64/share/cmake-3.21/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "C:/msys64/mingw64/share/cmake-3.21/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "ON")
set(CPACK_SOURCE_GENERATOR "7Z;ZIP")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/CPackSourceConfig.cmake")
set(CPACK_SOURCE_ZIP "ON")
set(CPACK_SYSTEM_NAME "win64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "win64")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "C:/Users/nilesh/Desktop/ego1155/WinLinux/DataProtection/Sources/plibsys/window/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()