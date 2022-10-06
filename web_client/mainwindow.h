#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

/*#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTcpSocket *socket;
    QByteArray data;

public slots:
    void socket_ready();
    void disconnect_socket();
    //void connect();

private:
    Ui::MainWindow *ui;
};*/



#endif // MAINWINDOW_H
