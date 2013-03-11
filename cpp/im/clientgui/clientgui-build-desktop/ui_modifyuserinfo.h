/********************************************************************************
** Form generated from reading UI file 'modifyuserinfo.ui'
**
** Created: Tue Jun 14 11:20:07 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYUSERINFO_H
#define UI_MODIFYUSERINFO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModifyUserinfo
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *labelUserno;
    QLabel *label_4;
    QLineEdit *lineEditPasswd;
    QLabel *label_6;
    QLineEdit *lineEditUsername;
    QLabel *label_5;
    QLineEdit *lineEditPasswd2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QWidget *layoutWidget1;
    QFormLayout *formLayout_2;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEditEmaile;
    QLabel *label_7;
    QLineEdit *lineEditName;
    QComboBox *comboBoxSex;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_5;
    QWidget *layoutWidget2;
    QFormLayout *formLayout_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QDialog *ModifyUserinfo)
    {
        if (ModifyUserinfo->objectName().isEmpty())
            ModifyUserinfo->setObjectName(QString::fromUtf8("ModifyUserinfo"));
        ModifyUserinfo->resize(568, 239);
        QFont font;
        font.setFamily(QString::fromUtf8("AlArabiya"));
        font.setPointSize(12);
        ModifyUserinfo->setFont(font);
        label = new QLabel(ModifyUserinfo);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 10, 191, 21));
        layoutWidget = new QWidget(ModifyUserinfo);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 40, 291, 191));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        labelUserno = new QLabel(layoutWidget);
        labelUserno->setObjectName(QString::fromUtf8("labelUserno"));

        formLayout->setWidget(0, QFormLayout::FieldRole, labelUserno);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        lineEditPasswd = new QLineEdit(layoutWidget);
        lineEditPasswd->setObjectName(QString::fromUtf8("lineEditPasswd"));
        lineEditPasswd->setMaxLength(32);
        lineEditPasswd->setEchoMode(QLineEdit::Normal);

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditPasswd);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_6);

        lineEditUsername = new QLineEdit(layoutWidget);
        lineEditUsername->setObjectName(QString::fromUtf8("lineEditUsername"));
        lineEditUsername->setMaxLength(64);

        formLayout->setWidget(6, QFormLayout::FieldRole, lineEditUsername);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        lineEditPasswd2 = new QLineEdit(layoutWidget);
        lineEditPasswd2->setObjectName(QString::fromUtf8("lineEditPasswd2"));
        lineEditPasswd2->setMaxLength(32);
        lineEditPasswd2->setEchoMode(QLineEdit::Normal);

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEditPasswd2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(1, QFormLayout::LabelRole, verticalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::LabelRole, verticalSpacer_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(5, QFormLayout::LabelRole, verticalSpacer_3);

        layoutWidget1 = new QWidget(ModifyUserinfo);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(320, 40, 241, 143));
        formLayout_2 = new QFormLayout(layoutWidget1);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_8);

        label_9 = new QLabel(layoutWidget1);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_9);

        lineEditEmaile = new QLineEdit(layoutWidget1);
        lineEditEmaile->setObjectName(QString::fromUtf8("lineEditEmaile"));
        lineEditEmaile->setMaxLength(32);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, lineEditEmaile);

        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_7);

        lineEditName = new QLineEdit(layoutWidget1);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setMaxLength(64);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEditName);

        comboBoxSex = new QComboBox(layoutWidget1);
        comboBoxSex->setObjectName(QString::fromUtf8("comboBoxSex"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, comboBoxSex);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_2->setItem(1, QFormLayout::LabelRole, verticalSpacer_4);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_2->setItem(3, QFormLayout::LabelRole, verticalSpacer_5);

        layoutWidget2 = new QWidget(ModifyUserinfo);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(350, 190, 178, 41));
        formLayout_3 = new QFormLayout(layoutWidget2);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, pushButton_2);

        pushButton = new QPushButton(layoutWidget2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, pushButton);


        retranslateUi(ModifyUserinfo);

        QMetaObject::connectSlotsByName(ModifyUserinfo);
    } // setupUi

    void retranslateUi(QDialog *ModifyUserinfo)
    {
        ModifyUserinfo->setWindowTitle(QApplication::translate("ModifyUserinfo", "Modify User Informaiton", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ModifyUserinfo", "Modify User Information", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ModifyUserinfo", "Userno", 0, QApplication::UnicodeUTF8));
        labelUserno->setText(QApplication::translate("ModifyUserinfo", "Userno", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ModifyUserinfo", "PassWord", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ModifyUserinfo", "UserName", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ModifyUserinfo", "PassWord Again", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ModifyUserinfo", "Sex", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("ModifyUserinfo", "Emaile", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ModifyUserinfo", "Name", 0, QApplication::UnicodeUTF8));
        comboBoxSex->clear();
        comboBoxSex->insertItems(0, QStringList()
         << QApplication::translate("ModifyUserinfo", "male", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModifyUserinfo", "female", 0, QApplication::UnicodeUTF8)
        );
        pushButton_2->setText(QApplication::translate("ModifyUserinfo", "Cancel", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ModifyUserinfo", "Commit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ModifyUserinfo: public Ui_ModifyUserinfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYUSERINFO_H
