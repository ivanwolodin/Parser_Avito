#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QVariant>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
     QNetworkAccessManager *manager;
     QTimer timeR;
     int n;
     int old_number_of_Cars;
     int new_number_of_Cars;

signals:
     void downloaded(); //испускается когда происходит выгрузка html кода
     void emailed();    //


private:
    Ui::Widget *ui;
public slots:
    void send_email();
    void doDownload();
    void replyFinished(QNetworkReply *reply);
    void Search_in_file();

};

#endif // WIDGET_H
