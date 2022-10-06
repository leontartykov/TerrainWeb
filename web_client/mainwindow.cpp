#include "mainwindow.h"
#include "./ui_mainwindow.h"

/*MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);


    connect(socket, SIGNAL(readyRead()), this, SLOT(socket_ready()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnect_socket()));
    socket->connectToHost("127.0.0.1", 5555);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::socket_ready()
{
    if (socket->waitForConnected(500)){
        socket->waitForReadyRead(500);
        data = socket->readAll();
        qDebug() << data;
    }
}

void MainWindow::disconnect_socket()
{
    socket->deleteLater();
}*/

/*void MainWindow::connect()
{
    socket->connectToHost("127.0.0.1", 5555);
}*/

