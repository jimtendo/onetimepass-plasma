set(runner_SRCS 
    otprunner.cpp
)

add_library(krunner_onetimepass MODULE ${runner_SRCS})
target_link_libraries(krunner_onetimepass
                      Qt5::Widgets
                      KF5::I18n
                      KF5::Service
                      KF5::Runner
                      KF5::Wallet
                      ${Liboath_LIBRARIES})

install(TARGETS krunner_onetimepass DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES plasma-runner-onetimepass.desktop DESTINATION ${SERVICES_INSTALL_DIR})
