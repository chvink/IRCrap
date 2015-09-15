#include "ircmanager.h"
#include <QDebug>
#include "enum.h"

IrcManager::IrcManager(Ui::MainWindow * ui_, ChannelDisplay *serverView_, QTcpSocket *sock_)
   : ui(ui_),
     nick("tslr"),
     irl_name("blah blah"),
     serverView(serverView_),
     sock(sock_)
{

}

void IrcManager::recieve(const IrcMessage &message)
{
    // logic here
    serverView->append(message.getRaw());
    QString command = message.getCommand();
    QString response = "PONG " + message.getFirstParam();
    ChannelDisplay* disp;
    switch(str2command(command))
    {
        case IRC_COMMANDS::PING:
            sock->write(response.toStdString().c_str());
            break;
        case IRC_COMMANDS::PRIVMSG:
            disp = channel2index[message.channelAsMessage()];
            if(!disp) throw "Unknown channel";
            disp->append(message.stringAsMessage());
            break;
        case IRC_COMMANDS::OTHER:
        default:
            break;
    }
}

QString IrcManager::joinChannel(const QString &channel)
{

    ChannelDisplay * disp = new ChannelDisplay(ui->tabList);
    int index = ui->tabList->addTab(disp, channel);
    channel2index[channel] = disp;
    return "JOIN " + channel + "\r\n";
}

QString IrcManager::leaveChannel(const QString &channel)
{
    ChannelDisplay * disp = channel2index[channel];
    channel2index.erase(channel2index.find(channel));
    if(disp) delete disp;
    return "PART " + channel + "\r\n";
}

QString IrcManager::sendMessage(const QString &channel, const QString &msg)
{
    return "PRIVMSG " + channel + ":" + msg + "\r\n";
}
