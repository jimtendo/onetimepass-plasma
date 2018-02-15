set(onetimepass_SRCS 
    main.cpp
    mainwindow.cpp
    provider.cpp
)

qt5_add_resources(onetimepass_RCS resources.qrc)

add_executable(onetimepass ${onetimepass_SRCS} ${onetimepass_RCS})

target_link_libraries(onetimepass LINK_PUBLIC
                      Qt5::Widgets
                      Qt5::Quick
                      KF5::I18n
                      KF5::Service
                      KF5::Runner
                      KF5::Wallet
                      ${Liboath_LIBRARIES})

install(TARGETS onetimepass ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( PROGRAMS org.kde.onetimepass.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
