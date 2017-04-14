#include <QApplication>
//#include "SmtpClient/SmtpMime"
//#include "SmtpClient"
#include <widget.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget wdg;
    wdg.show();

    return a.exec();
}
