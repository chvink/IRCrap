#ifndef CHANNELDISPLAY_H
#define CHANNELDISPLAY_H

#include <QWidget>

namespace Ui {
class ChannelDisplay;
}

class ChannelDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelDisplay(QWidget *parent = 0);
    ~ChannelDisplay();

    void append(const QString & str);

private:
    Ui::ChannelDisplay *ui;
};

#endif // CHANNELDISPLAY_H
