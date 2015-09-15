#include "ircmessage.h"

IrcMessage::IrcMessage(const QString & raw_)
    : raw(raw_),
      command("")
{
    if(raw.isEmpty()) return;

    QStringList tokens = raw.split(" ");
    int num_tokens = tokens.size();

    if(tokens[0][0] == ':') {
        prefix = tokens[0];
        if(num_tokens > 1) {
            command = tokens[1];
        }

        for(size_t i = 2; i < tokens.size(); ++i)
        {
            tokenized_parameters.push_back(tokens[i]);
        }
        int firstSpace = raw.indexOf(" ");
        int secondSpace = raw.indexOf(" ", firstSpace+1);
        raw_parameters = raw.right( raw.size() - secondSpace - 1 );
    } else {
        command = tokens[0];
        for(size_t i = 1; i < tokens.size(); ++i)
        {
            tokenized_parameters.push_back(tokens[i]);
        }
        int firstSpace = raw.indexOf(" ");
        raw_parameters = raw.right( raw.size() - firstSpace - 1 );
    }

    int spaceAfterFirstParam = raw_parameters.indexOf(" ");
    raw2_parameters = raw_parameters.right(raw_parameters.size() - spaceAfterFirstParam - 2);

}

