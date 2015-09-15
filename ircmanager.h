#ifndef IRCMANAGER_H
#define IRCMANAGER_H

#include <QString>
#include "ircmessage.h"
#include "channeldisplay.h"
#include <QtNetwork/QTcpSocket>

#include "ui_mainwindow.h"

class IrcManager
{
public:
    IrcManager(Ui::MainWindow * ui_, ChannelDisplay *serverView_, QTcpSocket *sock_);

    QString nickQuery() const
    {
        return "NICK " + nick + "\r\n";
    }

    QString userQuery() const
    {
        return "USER " + nick + " 8 * : " + irl_name + "\r\n";
    }

    void recieve(const IrcMessage & message);

    QString joinChannel(const QString & channel);
    QString leaveChannel(const QString & channel);
    QString sendMessage(const QString & channel, const QString & msg);
private:
    std::map<QString, ChannelDisplay*> channel2index;
    ChannelDisplay *serverView;
    QTcpSocket *sock;

    Ui::MainWindow *ui;

    QString nick;
    QString irl_name;
};

#endif // IRCMANAGER_H
