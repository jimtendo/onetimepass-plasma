#include "mainwindow.h"

#include "provider.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
#include <QVariant>
#include <QDebug>

MainWindow::MainWindow(int &argc, char **argv) :
    QApplication(argc, argv)
{
    setApplicationDisplayName(tr("OneTimePass"));
    setApplicationVersion("0.1");
    
    // Make the application exit when window is closed
    setQuitOnLastWindowClosed(true);

    // Create Provider Singleton and register it
    qmlRegisterSingletonType<Provider>("org.kde.onetimepass.provider", 1, 0, "Provider", Provider::SingletonProvider);
    m_provider = Provider::singleton();
    
    // Make sure wallet is open
    if (!m_provider->isWalletOpen()) {
        // TODO
    }
    
    // Create QML Engine
    m_qmlEngine = new QQmlApplicationEngine(this);
    
    // Check to see if an argument (otpauth URL) was passed
    if (argc == 2) {
        QVariantMap addOTP = parseOTPAuthURL(argv[1]);
        m_qmlEngine->rootContext()->setContextProperty("addOTP", addOTP);
    }
    
    // Load Main Window
    m_qmlEngine->load(QUrl("qrc:/qml/MainWindow.qml"));
}

MainWindow::~MainWindow()
{
    delete m_qmlEngine;
}

QVariantMap MainWindow::parseOTPAuthURL(QString Url)
{
    QUrl otpUrl(Url);
    
    // Make sure it's an otpauth URL and also totp
    if (otpUrl.scheme().toLower() != "otpauth") return QVariantMap();
    if (otpUrl.host().toLower() != "totp") return QVariantMap();    

    QVariantMap addOTP;
    addOTP["scheme"]  = otpUrl.scheme();
    addOTP["type"]    = otpUrl.host();
    addOTP["path"]    = otpUrl.path().remove('/');
    addOTP["secret"]  = QUrlQuery(otpUrl.query()).queryItemValue("secret");
    
    return addOTP;
}
