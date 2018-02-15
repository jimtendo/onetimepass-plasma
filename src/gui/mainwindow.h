#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>

class Provider;
class QQmlApplicationEngine;

class MainWindow : public QApplication
{
    Q_OBJECT

public:
    explicit MainWindow(int &argc, char **argv);
    ~MainWindow();
    
private:
    QQmlApplicationEngine *m_qmlEngine;
    Provider *m_provider;
};

#endif // MAINWINDOW_H
