/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Jun 14 11:20:07 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionApply;
    QAction *actionSet_server;
    QAction *actionApply_id;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *userno;
    QLineEdit *lineEditUserno;
    QLabel *passwd;
    QLineEdit *lineEditPasswd;
    QSpacerItem *verticalSpacer;
    QPushButton *quit;
    QPushButton *login;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(274, 396);
        actionApply = new QAction(MainWindow);
        actionApply->setObjectName(QString::fromUtf8("actionApply"));
        QFont font;
        font.setFamily(QString::fromUtf8("Aharoni"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        actionApply->setFont(font);
        actionSet_server = new QAction(MainWindow);
        actionSet_server->setObjectName(QString::fromUtf8("actionSet_server"));
        actionSet_server->setFont(font);
        actionApply_id = new QAction(MainWindow);
        actionApply_id->setObjectName(QString::fromUtf8("actionApply_id"));
        actionApply_id->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 241, 101));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        userno = new QLabel(layoutWidget);
        userno->setObjectName(QString::fromUtf8("userno"));
        userno->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, userno);

        lineEditUserno = new QLineEdit(layoutWidget);
        lineEditUserno->setObjectName(QString::fromUtf8("lineEditUserno"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Aharoni"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        lineEditUserno->setFont(font1);
        lineEditUserno->setMaxLength(6);

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditUserno);

        passwd = new QLabel(layoutWidget);
        passwd->setObjectName(QString::fromUtf8("passwd"));
        passwd->setFont(font);

        formLayout->setWidget(3, QFormLayout::LabelRole, passwd);

        lineEditPasswd = new QLineEdit(layoutWidget);
        lineEditPasswd->setObjectName(QString::fromUtf8("lineEditPasswd"));
        lineEditPasswd->setFont(font);
        lineEditPasswd->setMaxLength(32);
        lineEditPasswd->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditPasswd);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(2, QFormLayout::FieldRole, verticalSpacer);

        quit = new QPushButton(centralWidget);
        quit->setObjectName(QString::fromUtf8("quit"));
        quit->setGeometry(QRect(60, 250, 151, 41));
        quit->setFont(font1);
        login = new QPushButton(centralWidget);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(60, 170, 151, 41));
        login->setFont(font1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 274, 27));
        QFont font2;
        font2.setPointSize(12);
        menuBar->setFont(font2);
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionSet_server);
        menu->addAction(actionApply_id);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionApply->setText(QApplication::translate("MainWindow", "apply", 0, QApplication::UnicodeUTF8));
        actionSet_server->setText(QApplication::translate("MainWindow", "set server", 0, QApplication::UnicodeUTF8));
        actionApply_id->setText(QApplication::translate("MainWindow", "apply id", 0, QApplication::UnicodeUTF8));
        userno->setText(QApplication::translate("MainWindow", "userno", 0, QApplication::UnicodeUTF8));
        passwd->setText(QApplication::translate("MainWindow", "passwd", 0, QApplication::UnicodeUTF8));
        lineEditPasswd->setInputMask(QString());
        lineEditPasswd->setText(QString());
        quit->setText(QApplication::translate("MainWindow", "quit", 0, QApplication::UnicodeUTF8));
        login->setText(QApplication::translate("MainWindow", "login", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
