#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SFML::Audio" for configuration "Release"
set_property(TARGET SFML::Audio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SFML::Audio PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/./sfml-audio.framework/Versions/3.0.0/sfml-audio"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-audio.framework/Versions/3.0.0/sfml-audio"
  )

list(APPEND _cmake_import_check_targets SFML::Audio )
list(APPEND _cmake_import_check_files_for_SFML::Audio "${_IMPORT_PREFIX}/./sfml-audio.framework/Versions/3.0.0/sfml-audio" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
