#ifndef IRCMESSAGE_H
#define IRCMESSAGE_H

#include <QString>
#include <QStringList>

#include <string>

class IrcMessage
{
public:
    IrcMessage(const QString & raw_);

    QString getRaw() const
    {
        return raw;
    }

    QString getPrefix() const
    {
        return prefix;
    }

    QString getCommand() const
    {
        return command;
    }

    QString getRawParams() const
    {
        return raw_parameters;
    }

    QString getRaw2Params() const
    {
        return raw2_parameters;
    }

    QStringList getParamList() const
    {
        return tokenized_parameters;
    }

    QString getFirstParam() const
    {
        return tokenized_parameters.first();
    }

    bool looksLikeMessage() const {
        return command == "PRIVMSG";
    }

    QString channelAsMessage() const {
        return tokenized_parameters.first();
    }

    QString senderAsMessage() const {
        int delim = prefix.indexOf("!");
        std::string tmp = prefix.toStdString();
        tmp = tmp.substr(1,delim-1);
        return QString(tmp.c_str());
    }

    QString stringAsMessage() const {
        QString result = "<";
        result += senderAsMessage();
        result += "> ";
        std::string tmp = raw2_parameters.toStdString();
        tmp.substr(1);
        result += QString(tmp.c_str());
        return result;
    }

private:
    QString raw;
    QString command;
    QString prefix;
    QString raw_parameters;
    QString raw2_parameters;
    QStringList tokenized_parameters;
};

#endif // IRCMESSAGE_H
