#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ircmessage.h"

#include <QtNetwork/QHostAddress>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serverView(0),
    manager(0)
{
    ui->setupUi(this);
    serverView = new ChannelDisplay(ui->tabList);
    ui->tabList->addTab(serverView, "Server");
    ui->tabList->setCurrentIndex(0);
    manager = new IrcManager(ui, serverView, &sock);

    enableConnect();

    connect(&sock, SIGNAL(connected()), this, SLOT(connected()));
    connect(&sock,SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(&sock,SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(&sock,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(ui->sendButton,SIGNAL(clicked(bool)),this,SLOT(issueQuery()));
    connect(ui->connectButton,SIGNAL(clicked(bool)),this,SLOT(connectToServer()));
    connect(&sock,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(error(QAbstractSocket::SocketError)));
    connect(ui->disconnectButton,SIGNAL(clicked(bool)),this,SLOT(disconnect()));
    connect(ui->queryEdit, SIGNAL(returnPressed()), this, SLOT(issueQuery()));
    connect(ui->joinButton, SIGNAL(clicked(bool)), this, SLOT(join()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

void MainWindow::sendMsg(const QString &msg)
{
    sock.write(msg.toStdString().c_str());
}

void MainWindow::connectToServer()
{
    serverView->append("Doing DNS lookup...");
    QHostInfo::lookupHost(ui->serverAddrEdit->text(),
                          this, SLOT(finishedLookup(QHostInfo)));
}

void MainWindow::finishedLookup(QHostInfo info)
{
    if(info.error())
    {
        serverView->append(info.errorString());
    }
    else
    {
        serverView->append("Connecting...");
        sock.connectToHost(info.addresses().first(), ui->portEdit->text().toInt());
    }
}

void MainWindow::disconnect()
{
    sock.close();
    enableConnect();
}

void MainWindow::connected()
{

    if(sock.isOpen())
    {
        serverView->append("Connected to " + sock.peerAddress().toString());
        enableChat();
    }
    else
    {
        serverView->append("Could not connect");
    }
}

void MainWindow::disconnected()
{
    serverView->append("Disconnected");
    enableConnect();
}

void MainWindow::bytesWritten(qint64 bytes)
{
    serverView->append("Sent: " + curQuery);
    ui->queryEdit->clear();
    ui->queryEdit->setFocus();
}

void MainWindow::readyRead()
{
    QString messages = sock.readAll();
    QStringList msgList = messages.split("\n");
    for(size_t i = 0; i < msgList.size(); ++i)
    {
        IrcMessage mess(msgList[i]);
        if(!mess.getCommand().isEmpty())
        {
            manager->recieve(msgList[i]);
        }
    }

}

void MainWindow::error(QAbstractSocket::SocketError err)
{
    QString msg;
    switch(err)
    {
        case QAbstractSocket::ConnectionRefusedError:
            msg = "Connection refused";
            break;
        case QAbstractSocket::RemoteHostClosedError:
            msg = "Remote host closed";
            break;
        case QAbstractSocket::HostNotFoundError:
            msg = "Host not found";
            break;
        case QAbstractSocket::SocketAccessError:
            msg = "Socket access error";
            break;
        case QAbstractSocket::SocketResourceError:
            msg = "Socket resource error";
            break;
        case QAbstractSocket::SocketTimeoutError:
            msg = "Socket timeout error";
            break;
        case QAbstractSocket::DatagramTooLargeError:
            msg = "Datagram too large error";
            break;
        case QAbstractSocket::NetworkError:
            msg = "Network error";
            break;
        case QAbstractSocket::AddressInUseError:
            msg = "Address in use";
            break;
        case QAbstractSocket::SocketAddressNotAvailableError:
            msg = "Socket address not available";
            break;
        case QAbstractSocket::UnsupportedSocketOperationError:
            msg = "Unsupported socket operation";
            break;
        case QAbstractSocket::ProxyAuthenticationRequiredError:
            msg = "Proxy authentication required";
            break;
        case QAbstractSocket::SslHandshakeFailedError:
            msg = "SSL handshake failed";
            break;
        case QAbstractSocket::UnfinishedSocketOperationError:
            msg = "Unfinished socket operation";
            break;
        case QAbstractSocket::ProxyConnectionRefusedError:
        case QAbstractSocket::ProxyConnectionClosedError:
        case QAbstractSocket::ProxyConnectionTimeoutError:
        case QAbstractSocket::ProxyNotFoundError:
        case QAbstractSocket::ProxyProtocolError:
            msg = "Proxy error";
            break;
        case QAbstractSocket::UnknownSocketError:
        default:
            msg = "Unknown socket error";
            break;
    }

    serverView->append(msg);
    enableConnect();
}

void MainWindow::join()
{
    QString channel = ui->joinEdit->text();
    sendMsg(manager->joinChannel(channel));
}

void MainWindow::leave()
{

}

void MainWindow::issueQuery()
{
    curQuery = ui->queryEdit->text();
    curQuery += "\r\n";
    sock.write(curQuery.toStdString().c_str(),curQuery.length());
}

void MainWindow::enableChat()
{
    ui->sendButton->setEnabled(true);
    ui->queryEdit->setEnabled(true);
    ui->connectButton->setEnabled(false);
    ui->serverAddrEdit->setEnabled(false);
    ui->portEdit->setEnabled(false);
    ui->disconnectButton->setEnabled(true);
    ui->joinEdit->setEnabled(true);
    ui->joinButton->setEnabled(true);
}

void MainWindow::enableConnect()
{
    ui->sendButton->setEnabled(false);
    ui->queryEdit->setEnabled(false);
    ui->connectButton->setEnabled(true);
    ui->serverAddrEdit->setEnabled(true);
    ui->portEdit->setEnabled(true);
    ui->disconnectButton->setEnabled(false);
    ui->joinEdit->setEnabled(false);
    ui->joinButton->setEnabled(false);
}
