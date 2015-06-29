#include "widget.h"
#include <QApplication>
#include "shanbay.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    Shanbay sb;
    bool ok = false;
ShanbayWord info = sb.syncGetWord("silence",&ok);
qDebug() << info.content << info.pronunciation << info.en_definitions << info.cn_definition;
    return a.exec();
}
