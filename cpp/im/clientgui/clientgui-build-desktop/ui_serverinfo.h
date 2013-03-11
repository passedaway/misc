/********************************************************************************
** Form generated from reading UI file 'serverinfo.ui'
**
** Created: Tue Jun 14 11:20:07 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERINFO_H
#define UI_SERVERINFO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ServerInfo
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEditIp;
    QLineEdit *lineEditPort;
    QPushButton *pushButtonOK;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *ServerInfo)
    {
        if (ServerInfo->objectName().isEmpty())
            ServerInfo->setObjectName(QString::fromUtf8("ServerInfo"));
        ServerInfo->resize(327, 210);
        QFont font;
        font.setFamily(QString::fromUtf8("Aharoni"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        ServerInfo->setFont(font);
        ServerInfo->setFocusPolicy(Qt::TabFocus);
        ServerInfo->setAutoFillBackground(false);
        label = new QLabel(ServerInfo);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 10, 241, 51));
        label_2 = new QLabel(ServerInfo);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 70, 31, 16));
        label_3 = new QLabel(ServerInfo);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 110, 54, 21));
        lineEditIp = new QLineEdit(ServerInfo);
        lineEditIp->setObjectName(QString::fromUtf8("lineEditIp"));
        lineEditIp->setGeometry(QRect(90, 69, 171, 21));
        lineEditPort = new QLineEdit(ServerInfo);
        lineEditPort->setObjectName(QString::fromUtf8("lineEditPort"));
        lineEditPort->setGeometry(QRect(90, 110, 113, 20));
        pushButtonOK = new QPushButton(ServerInfo);
        pushButtonOK->setObjectName(QString::fromUtf8("pushButtonOK"));
        pushButtonOK->setGeometry(QRect(150, 170, 75, 31));
        pushButtonCancel = new QPushButton(ServerInfo);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(240, 170, 75, 31));

        retranslateUi(ServerInfo);

        QMetaObject::connectSlotsByName(ServerInfo);
    } // setupUi

    void retranslateUi(QDialog *ServerInfo)
    {
        ServerInfo->setWindowTitle(QApplication::translate("ServerInfo", "set server information", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ServerInfo", "SET SERVER INFOMATION", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ServerInfo", "IP", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ServerInfo", "PORT", 0, QApplication::UnicodeUTF8));
        lineEditIp->setText(QApplication::translate("ServerInfo", "192.168.1.120", 0, QApplication::UnicodeUTF8));
        lineEditPort->setText(QApplication::translate("ServerInfo", "8800", 0, QApplication::UnicodeUTF8));
        pushButtonOK->setText(QApplication::translate("ServerInfo", "OK", 0, QApplication::UnicodeUTF8));
        pushButtonCancel->setText(QApplication::translate("ServerInfo", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ServerInfo: public Ui_ServerInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERINFO_H
