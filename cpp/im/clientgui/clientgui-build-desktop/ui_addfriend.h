/********************************************************************************
** Form generated from reading UI file 'addfriend.ui'
**
** Created: Tue Jun 14 11:20:07 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIEND_H
#define UI_ADDFRIEND_H

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

class Ui_AddFriend
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEditUserno;
    QLineEdit *lineEditNickname;
    QPushButton *pushButtonOk;
    QPushButton *pushButtonCancel;
    QLabel *label_3;

    void setupUi(QDialog *AddFriend)
    {
        if (AddFriend->objectName().isEmpty())
            AddFriend->setObjectName(QString::fromUtf8("AddFriend"));
        AddFriend->resize(411, 205);
        QFont font;
        font.setFamily(QString::fromUtf8("AlArabiya"));
        font.setPointSize(12);
        AddFriend->setFont(font);
        label = new QLabel(AddFriend);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 50, 141, 31));
        label->setFont(font);
        label_2 = new QLabel(AddFriend);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 100, 211, 21));
        lineEditUserno = new QLineEdit(AddFriend);
        lineEditUserno->setObjectName(QString::fromUtf8("lineEditUserno"));
        lineEditUserno->setGeometry(QRect(190, 50, 151, 31));
        lineEditUserno->setMaxLength(6);
        lineEditNickname = new QLineEdit(AddFriend);
        lineEditNickname->setObjectName(QString::fromUtf8("lineEditNickname"));
        lineEditNickname->setGeometry(QRect(240, 100, 161, 31));
        lineEditNickname->setMaxLength(64);
        pushButtonOk = new QPushButton(AddFriend);
        pushButtonOk->setObjectName(QString::fromUtf8("pushButtonOk"));
        pushButtonOk->setGeometry(QRect(50, 150, 121, 41));
        pushButtonCancel = new QPushButton(AddFriend);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(220, 150, 121, 41));
        label_3 = new QLabel(AddFriend);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(150, 10, 91, 16));
        QFont font1;
        font1.setPointSize(14);
        label_3->setFont(font1);

        retranslateUi(AddFriend);

        QMetaObject::connectSlotsByName(AddFriend);
    } // setupUi

    void retranslateUi(QDialog *AddFriend)
    {
        AddFriend->setWindowTitle(QApplication::translate("AddFriend", "Add Friend", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddFriend", "Input Friend Userno", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AddFriend", "Give Your Friend a nickname", 0, QApplication::UnicodeUTF8));
        pushButtonOk->setText(QApplication::translate("AddFriend", "Commit", 0, QApplication::UnicodeUTF8));
        pushButtonCancel->setText(QApplication::translate("AddFriend", "Cancel", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AddFriend", "Add Friend", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddFriend: public Ui_AddFriend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIEND_H
