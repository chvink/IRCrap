#ifndef ENUM
#define ENUM

namespace IRC_COMMANDS
{
enum CMD
{
    PING,
    PRIVMSG,
    OTHER
};
}

IRC_COMMANDS::CMD str2command(const QString & str)
{
    if(str == "PING")
    {
        return IRC_COMMANDS::PING;
    }
    else if (str == "PRIVMSG")
    {
        return IRC_COMMANDS::PRIVMSG;
    }
    else
    {
        return IRC_COMMANDS::OTHER;
    }

}

#endif // ENUM

