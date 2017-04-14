#-------------------------------------------------
#
# Project created by QtCreator 2017-02-28T20:29:35
#
#-------------------------------------------------

QT       += core gui
QT += core network

# Build as an application
#TEMPLATE = app

win32{
    LIBS += -L C:/OpenSSL-Win32/lib -lubsec
    INCLUDEPATH += C:/OpenSSL-Win32/include
}


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = www
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        widget.cpp \
    SmtpClient/emailaddress.cpp \
    SmtpClient/mimeattachment.cpp \
    SmtpClient/mimefile.cpp \
    SmtpClient/mimehtml.cpp \
    SmtpClient/mimeinlinefile.cpp \
    SmtpClient/mimemessage.cpp \
    SmtpClient/mimepart.cpp \
    SmtpClient/mimetext.cpp \
    SmtpClient/smtpclient.cpp \
    SmtpClient/quotedprintable.cpp \
    SmtpClient/mimemultipart.cpp \
    SmtpClient/mimecontentformatter.cpp \

HEADERS  += widget.h \
      SmtpClient/emailaddress.h \
      SmtpClient/mimeattachment.h \
      SmtpClient/mimefile.h \
      SmtpClient/mimehtml.h \
      SmtpClient/mimeinlinefile.h \
      SmtpClient/mimemessage.h \
      SmtpClient/mimepart.h \
      SmtpClient/mimetext.h \
      SmtpClient/smtpclient.h \
      SmtpClient/SmtpMime \
      SmtpClient/quotedprintable.h \
      SmtpClient/mimemultipart.h \
      SmtpClient/mimecontentformatter.h \
     SmtpClient/smtpexports.h

FORMS    += widget.ui
