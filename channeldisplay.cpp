#include "channeldisplay.h"
#include "ui_channeldisplay.h"
#include <QDebug>
#include <QRegExp>

#include <string>

ChannelDisplay::ChannelDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelDisplay)
{
    ui->setupUi(this);
}

ChannelDisplay::~ChannelDisplay()
{
    delete ui;
}

void ChannelDisplay::append(const QString &str)
{
    if(str.isEmpty()) return;
    QString qstr = str;
    qstr = qstr.remove(QRegExp("[\\n\\t\\r]"));
    ui->view->append(qstr);
}
