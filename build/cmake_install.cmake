# Install script for directory: /home/vishwas/Vault/1.Projects/PICO/pico/picotool

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/picotool" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/picotool")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/picotool"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/vishwas/Vault/1.Projects/PICO/pico/build/picotool")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/picotool" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/picotool")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/picotool")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/picotool/picotoolTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/picotool/picotoolTargets.cmake"
         "/home/vishwas/Vault/1.Projects/PICO/pico/build/CMakeFiles/Export/lib/cmake/picotool/picotoolTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/picotool/picotoolTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/picotool/picotoolTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/picotool" TYPE FILE FILES "/home/vishwas/Vault/1.Projects/PICO/pico/build/CMakeFiles/Export/lib/cmake/picotool/picotoolTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/picotool" TYPE FILE FILES "/home/vishwas/Vault/1.Projects/PICO/pico/build/CMakeFiles/Export/lib/cmake/picotool/picotoolTargets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/picotool" TYPE FILE FILES
    "/home/vishwas/Vault/1.Projects/PICO/pico/build/picotoolConfig.cmake"
    "/home/vishwas/Vault/1.Projects/PICO/pico/build/picotoolConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/picotool" TYPE FILE FILES "/home/vishwas/Vault/1.Projects/PICO/pico/build/rp2350_otp_contents.json")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/picotool" TYPE FILE FILES "/home/vishwas/Vault/1.Projects/PICO/pico/build/xip_ram_perms/xip_ram_perms.elf")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/vishwas/Vault/1.Projects/PICO/pico/build/errors/cmake_install.cmake")
  include("/home/vishwas/Vault/1.Projects/PICO/pico/build/picoboot_connection/cmake_install.cmake")
  include("/home/vishwas/Vault/1.Projects/PICO/pico/build/elf/cmake_install.cmake")
  include("/home/vishwas/Vault/1.Projects/PICO/pico/build/elf2uf2/cmake_install.cmake")
  include("/home/vishwas/Vault/1.Projects/PICO/pico/build/lib/cmake_install.cmake")
  include("/home/vishwas/Vault/1.Projects/PICO/pico/build/bintool/cmake_install.cmake")
  include("/home/vishwas/Vault/1.Projects/PICO/pico/build/pico_binary_info/cmake_install.cmake")
  include("/home/vishwas/Vault/1.Projects/PICO/pico/build/boot_uf2_headers/cmake_install.cmake")
  include("/home/vishwas/Vault/1.Projects/PICO/pico/build/boot_picoboot_headers/cmake_install.cmake")
  include("/home/vishwas/Vault/1.Projects/PICO/pico/build/boot_picobin_headers/cmake_install.cmake")
  include("/home/vishwas/Vault/1.Projects/PICO/pico/build/pico_usb_reset_interface_headers/cmake_install.cmake")
  include("/home/vishwas/Vault/1.Projects/PICO/pico/build/boot_bootrom_headers/cmake_install.cmake")
  include("/home/vishwas/Vault/1.Projects/PICO/pico/build/pico_platform/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/vishwas/Vault/1.Projects/PICO/pico/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
