/********************************************************************************
** Form generated from reading UI file 'addfriendreply.ui'
**
** Created: Tue Jun 14 11:20:07 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIENDREPLY_H
#define UI_ADDFRIENDREPLY_H

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

class Ui_AddFriendReply
{
public:
    QLabel *statusLabel;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButtonAgree;
    QPushButton *pushButtonDisagree;

    void setupUi(QDialog *AddFriendReply)
    {
        if (AddFriendReply->objectName().isEmpty())
            AddFriendReply->setObjectName(QString::fromUtf8("AddFriendReply"));
        AddFriendReply->resize(312, 186);
        statusLabel = new QLabel(AddFriendReply);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(20, 20, 251, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("AlArabiya"));
        font.setPointSize(12);
        statusLabel->setFont(font);
        label = new QLabel(AddFriendReply);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 70, 131, 21));
        lineEdit = new QLineEdit(AddFriendReply);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(80, 90, 191, 31));
        pushButtonAgree = new QPushButton(AddFriendReply);
        pushButtonAgree->setObjectName(QString::fromUtf8("pushButtonAgree"));
        pushButtonAgree->setGeometry(QRect(30, 140, 101, 31));
        pushButtonDisagree = new QPushButton(AddFriendReply);
        pushButtonDisagree->setObjectName(QString::fromUtf8("pushButtonDisagree"));
        pushButtonDisagree->setGeometry(QRect(150, 140, 101, 31));

        retranslateUi(AddFriendReply);

        QMetaObject::connectSlotsByName(AddFriendReply);
    } // setupUi

    void retranslateUi(QDialog *AddFriendReply)
    {
        AddFriendReply->setWindowTitle(QApplication::translate("AddFriendReply", "Add Friend Request", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QApplication::translate("AddFriendReply", "TextLabel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddFriendReply", "Give it a nickname", 0, QApplication::UnicodeUTF8));
        pushButtonAgree->setText(QApplication::translate("AddFriendReply", "Agree", 0, QApplication::UnicodeUTF8));
        pushButtonDisagree->setText(QApplication::translate("AddFriendReply", "Disagree", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddFriendReply: public Ui_AddFriendReply {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIENDREPLY_H
