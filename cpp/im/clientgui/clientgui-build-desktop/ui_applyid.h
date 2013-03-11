/********************************************************************************
** Form generated from reading UI file 'applyid.ui'
**
** Created: Tue Jun 14 11:20:07 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLYID_H
#define UI_APPLYID_H

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

class Ui_ApplyId
{
public:
    QLabel *label;
    QLabel *statusLabel;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *userno;
    QLabel *label_3;
    QLineEdit *lineEditUsername;
    QLabel *label_4;
    QLineEdit *lineEditPasswd;
    QLabel *label_5;
    QLineEdit *lineEditPasswd2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_5;
    QWidget *layoutWidget1;
    QFormLayout *formLayout_2;
    QLabel *label_6;
    QLineEdit *lineEditName;
    QLabel *label_7;
    QComboBox *comboBoxSex;
    QLabel *label_8;
    QLineEdit *lineEditEmaile;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QWidget *layoutWidget2;
    QFormLayout *formLayout_3;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonCommit;

    void setupUi(QDialog *ApplyId)
    {
        if (ApplyId->objectName().isEmpty())
            ApplyId->setObjectName(QString::fromUtf8("ApplyId"));
        ApplyId->resize(574, 248);
        QFont font;
        font.setFamily(QString::fromUtf8("Aharoni"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        ApplyId->setFont(font);
        ApplyId->setFocusPolicy(Qt::TabFocus);
        label = new QLabel(ApplyId);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 0, 111, 31));
        statusLabel = new QLabel(ApplyId);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(130, 30, 321, 31));
        layoutWidget = new QWidget(ApplyId);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 70, 321, 141));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Aharoni"));
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        userno = new QLabel(layoutWidget);
        userno->setObjectName(QString::fromUtf8("userno"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("AlArabiya"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        userno->setFont(font2);

        formLayout->setWidget(0, QFormLayout::FieldRole, userno);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        lineEditUsername = new QLineEdit(layoutWidget);
        lineEditUsername->setObjectName(QString::fromUtf8("lineEditUsername"));
        lineEditUsername->setEnabled(true);
        lineEditUsername->setFont(font1);
        lineEditUsername->setMaxLength(32);

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditUsername);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        lineEditPasswd = new QLineEdit(layoutWidget);
        lineEditPasswd->setObjectName(QString::fromUtf8("lineEditPasswd"));
        lineEditPasswd->setFont(font1);
        lineEditPasswd->setMaxLength(32);

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEditPasswd);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        formLayout->setWidget(6, QFormLayout::LabelRole, label_5);

        lineEditPasswd2 = new QLineEdit(layoutWidget);
        lineEditPasswd2->setObjectName(QString::fromUtf8("lineEditPasswd2"));
        lineEditPasswd2->setFont(font1);
        lineEditPasswd2->setMaxLength(32);

        formLayout->setWidget(6, QFormLayout::FieldRole, lineEditPasswd2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(1, QFormLayout::LabelRole, verticalSpacer_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::LabelRole, verticalSpacer_4);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(5, QFormLayout::LabelRole, verticalSpacer_5);

        layoutWidget1 = new QWidget(ApplyId);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(340, 70, 231, 121));
        formLayout_2 = new QFormLayout(layoutWidget1);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_6);

        lineEditName = new QLineEdit(layoutWidget1);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setFont(font1);
        lineEditName->setMaxLength(32);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEditName);

        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font1);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_7);

        comboBoxSex = new QComboBox(layoutWidget1);
        comboBoxSex->setObjectName(QString::fromUtf8("comboBoxSex"));
        comboBoxSex->setFont(font1);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, comboBoxSex);

        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font1);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_8);

        lineEditEmaile = new QLineEdit(layoutWidget1);
        lineEditEmaile->setObjectName(QString::fromUtf8("lineEditEmaile"));
        lineEditEmaile->setFont(font1);
        lineEditEmaile->setMaxLength(32);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, lineEditEmaile);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_2->setItem(1, QFormLayout::LabelRole, verticalSpacer);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout_2->setItem(3, QFormLayout::LabelRole, verticalSpacer_2);

        layoutWidget2 = new QWidget(ApplyId);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(380, 210, 182, 31));
        formLayout_3 = new QFormLayout(layoutWidget2);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButtonCancel = new QPushButton(layoutWidget2);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Aharoni"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        pushButtonCancel->setFont(font3);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, pushButtonCancel);

        pushButtonCommit = new QPushButton(layoutWidget2);
        pushButtonCommit->setObjectName(QString::fromUtf8("pushButtonCommit"));
        pushButtonCommit->setFont(font3);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, pushButtonCommit);


        retranslateUi(ApplyId);

        QMetaObject::connectSlotsByName(ApplyId);
    } // setupUi

    void retranslateUi(QDialog *ApplyId)
    {
        ApplyId->setWindowTitle(QApplication::translate("ApplyId", "Apply ID", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ApplyId", "Apply ID", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QString());
        label_2->setText(QApplication::translate("ApplyId", "Userno", 0, QApplication::UnicodeUTF8));
        userno->setText(QApplication::translate("ApplyId", "userno", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ApplyId", "Username", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ApplyId", "Password", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ApplyId", "Password Again", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ApplyId", "name", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ApplyId", "Sex", 0, QApplication::UnicodeUTF8));
        comboBoxSex->clear();
        comboBoxSex->insertItems(0, QStringList()
         << QApplication::translate("ApplyId", "male", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ApplyId", "female", 0, QApplication::UnicodeUTF8)
        );
        label_8->setText(QApplication::translate("ApplyId", "Emaile", 0, QApplication::UnicodeUTF8));
        pushButtonCancel->setText(QApplication::translate("ApplyId", "Cancel", 0, QApplication::UnicodeUTF8));
        pushButtonCommit->setText(QApplication::translate("ApplyId", "Commit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ApplyId: public Ui_ApplyId {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLYID_H
