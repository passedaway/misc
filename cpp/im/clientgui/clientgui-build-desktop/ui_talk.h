/********************************************************************************
** Form generated from reading UI file 'talk.ui'
**
** Created: Tue Jun 14 11:20:07 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TALK_H
#define UI_TALK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_talk
{
public:
    QTextEdit *textEdit;
    QPushButton *pushButtonSend;
    QPushButton *pushButtonClose;
    QListWidget *listWidget;

    void setupUi(QDialog *talk)
    {
        if (talk->objectName().isEmpty())
            talk->setObjectName(QString::fromUtf8("talk"));
        talk->resize(402, 332);
        textEdit = new QTextEdit(talk);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(0, 210, 391, 84));
        pushButtonSend = new QPushButton(talk);
        pushButtonSend->setObjectName(QString::fromUtf8("pushButtonSend"));
        pushButtonSend->setGeometry(QRect(300, 300, 93, 27));
        pushButtonClose = new QPushButton(talk);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(200, 300, 93, 27));
        listWidget = new QListWidget(talk);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 391, 191));
        listWidget->setAutoScroll(true);
        listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

        retranslateUi(talk);

        listWidget->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(talk);
    } // setupUi

    void retranslateUi(QDialog *talk)
    {
        talk->setWindowTitle(QApplication::translate("talk", "talk", 0, QApplication::UnicodeUTF8));
        pushButtonSend->setText(QApplication::translate("talk", "&Send", 0, QApplication::UnicodeUTF8));
        pushButtonClose->setText(QApplication::translate("talk", "&Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class talk: public Ui_talk {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TALK_H
