#include "mainwindow.h"

#include "provider.h"

#include <QQmlApplicationEngine>
#include <QString>

MainWindow::MainWindow(int &argc, char **argv) :
    QApplication(argc, argv)
{
    setApplicationDisplayName(tr("OneTimePass"));
    setApplicationVersion("0.1");
    
    

    // Make the application exit when window is closed
    connect(this, SIGNAL(lastWindowClosed()), this, SLOT(quit()));

    // Create Provider Singleton and register it
    qmlRegisterSingletonType<Provider>("org.kde.onetimepass.provider", 1, 0, "Provider", Provider::SingletonProvider);
    m_provider = Provider::singleton();
    
    // Create QML Engine
    m_qmlEngine = new QQmlApplicationEngine(this);
    m_qmlEngine->load(QUrl("qrc:/qml/MainWindow.qml"));
}

MainWindow::~MainWindow()
{

}
