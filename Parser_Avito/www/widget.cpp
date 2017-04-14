#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QDebug>
#include "SmtpClient/SmtpMime"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
     //timeR=new QTimer();

   // timeR.setInterval(60000);

   // connect(ui->pushButtonSend,SIGNAL(clicked(bool)),SLOT(send_email()));
  //  connect(timeR,SIGNAL(timeout()),this,SLOT(doDownload()));

    connect(&timeR,SIGNAL(timeout()),this,SLOT(doDownload()));
    timeR.start(60000);

    connect(this,SIGNAL(downloaded()),this,SLOT(Search_in_file()));
    connect(this,SIGNAL(emailed()),this,SLOT(send_email()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::send_email()
{
    qDebug()<<"Send Email"<<endl;
   // QString strinng1;
  //  strinng1=ui->textEdit->toPlainText();
    //qDebug()<<strinng1<<endl;
    // This is a first demo application of the SmtpClient for Qt project

    // First we need to create an SmtpClient object
    // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

    // We need to set the username (your email address) and the password
    // for smtp authentification.

    smtp.setUser("ivanwolodin@gmail.com");
    smtp.setPassword("mULTIVERSUM8");

    // Now we create a MimeMessage object. This will be the email.

    MimeMessage message;

    message.setSender(new EmailAddress("ivanwolodin@gmail.com", "Ivan"));
    message.addRecipient(new EmailAddress("master.johnus@gmail.com", "Recipient's Name"));
    message.setSubject(" Дешёвое предложение на Авито! ");

    // Now add some text to the email.
    // First we create a MimeText object.

    MimeText text;

    text.setText("Количество машин изменилось!");

    // Now add it to the mail

    message.addPart(&text);

    // Now we can send the mail

    smtp.connectToHost();
    smtp.login();
    smtp.sendMail(message);
    smtp.quit();

}

void Widget::doDownload()
{
     qDebug()<<"doDownload()"<<endl;
    manager = new QNetworkAccessManager(this);

       connect(manager, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(replyFinished(QNetworkReply*)));

       manager->get(QNetworkRequest(QUrl("https://www.avito.ru/rossiya/avtomobili/renault/scenic/polnyy_privod?f=188_0b896")));
}

void Widget::replyFinished(QNetworkReply *reply)
{
     qDebug()<<"replyFinished"<<endl;
    if(reply->error() != QNetworkReply::NoError)
        {
            qDebug() << "ERROR!";
            qDebug() << reply->errorString();
        }
        else
        {
            qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
            qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
            qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
            qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

            QFile file("C:/Qt/Dummy/downloaded.txt");
            if(file.open(QFile::WriteOnly))
            {
                file.write(reply->readAll());
            }
            file.close();
        }


    reply->deleteLater();
    emit downloaded(); // испустили сигнал ! теперь нужно искать в файле и испустить сигнал emailed();

}

void Widget::Search_in_file()
{
    old_number_of_Cars=n; // сохраняем количество старых машин
     qDebug()<<"Search in file"<<endl;
    int number_of_matching;
    QString analysing_string;
    QFile file("C:/Qt/Dummy/downloaded.txt");
        if(file.open(QIODevice::ReadOnly |QIODevice::Text))
        {
            while(!file.atEnd())
            {
                //читаем строку //читаем построчно
                QString str = file.readLine();


            number_of_matching= str.indexOf("catalog-counts__number");

            QStringList lst = str.split("catalog-counts__number ");



            if(number_of_matching!=-1){//нужно первое вхождение
                qDebug()<<"number_of_matching= "<<number_of_matching<<endl;
              //  qDebug()<< str.at(number_of_matching+25).toLatin1()<<endl; //организуем проверку на то - число это или нет
               analysing_string=str;
                break;

            }

            }

        }
        else
        {
            qDebug()<< "don't open file";
        }

     //   QString str = "......catalog-counts__number> 23 < .......";
        QString s = "catalog-counts__number> ";
        qDebug()<<analysing_string<<endl;
        int ind = analysing_string.indexOf("catalog-counts__number\"> ");
        qDebug()<<ind<<endl;
        if (ind != - 1)
        {
            int begin = ind + s.size();
            int end = analysing_string.indexOf('<', begin);
            if (end != -1)
            {
                QString number = analysing_string.mid(begin, end - begin);
                int n = number.toInt();
                qDebug()<<"n= "<<n<<endl;
            }
        }
        // сделать проверку на изменение
        if(old_number_of_Cars!=n){
        emit emailed(); //после этого нужно отправлять письмо!
            ui->textEdit->setText("Email sent!\n");
        }
}
