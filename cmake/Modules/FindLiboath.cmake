# Try to find Liboath library
# Once done this will define
#  Liboath_FOUND - if system found Liboath library
#  Liboath_INCLUDE_DIRS - The Liboath include directories
#  Liboath_LIBRARIES - The libraries needed to use Liboath
#  Liboath_DEFINITIONS - Compiler switches required for using Liboath

find_path(Liboath_INCLUDE_DIR
    NAMES oath.h liboath/oath.h
    PATHS /usr/include
    DOC "The Liboath include directory"
)

find_library(Liboath_LIBRARY 
    NAMES oath
    PATHS /usr/lib
    DOC "The Liboath library"
)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LOGGING_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Liboath DEFAULT_MSG Liboath_INCLUDE_DIR Liboath_LIBRARY)

if (Liboath_FOUND)
    set(Liboath_LIBRARIES ${Liboath_LIBRARY} )
    set(Liboath_INCLUDE_DIRS ${Liboath_INCLUDE_DIR} )
    set(Liboath_DEFINITIONS )
endif()
