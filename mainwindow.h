#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "channeldisplay.h"
#include "ircmanager.h"
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QDnsLookup>
#include <QtNetwork/QHostInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void sendMsg(const QString & msg);

public slots:

    void connectToServer();
    void finishedLookup(QHostInfo info);

    void disconnect();

    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void error(QAbstractSocket::SocketError err);
    void join();
    void leave();

    void issueQuery();

private:
    Ui::MainWindow *ui;
    QTcpSocket sock;

    QString curQuery;

    ChannelDisplay * serverView;
    IrcManager * manager;

    void enableChat();
    void enableConnect();
};

#endif // MAINWINDOW_H
