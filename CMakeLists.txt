cmake_minimum_required(VERSION 2.8.12)

project(OneTimePass)

set(KF5_VERSION "5.24.0")
find_package(ECM ${KF5_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Find the required Libaries
find_package(Qt5 5.7.0 CONFIG REQUIRED Core Gui Widgets Quick)
find_package (Liboath REQUIRED)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)
include(ECMInstallIcons)
include(ECMAddAppIcon)
include(ECMSetupVersion)



find_package(KF5 ${KF5_VERSION} REQUIRED
    I18n
    Service
    Runner
    Wallet
)

include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${Liboath_INCLUDE_DIRS}
)

add_subdirectory(src)
