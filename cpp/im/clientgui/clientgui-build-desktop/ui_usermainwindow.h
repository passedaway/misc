/********************************************************************************
** Form generated from reading UI file 'usermainwindow.ui'
**
** Created: Tue Jun 14 11:20:07 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMAINWINDOW_H
#define UI_USERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserMainWindow
{
public:
    QAction *actionModifyUserinfo;
    QAction *actionAddFriend;
    QAction *actionExit;
    QWidget *centralwidget;
    QLabel *usernoLabel;
    QTreeWidget *treeWidget;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *UserMainWindow)
    {
        if (UserMainWindow->objectName().isEmpty())
            UserMainWindow->setObjectName(QString::fromUtf8("UserMainWindow"));
        UserMainWindow->resize(264, 483);
        actionModifyUserinfo = new QAction(UserMainWindow);
        actionModifyUserinfo->setObjectName(QString::fromUtf8("actionModifyUserinfo"));
        actionAddFriend = new QAction(UserMainWindow);
        actionAddFriend->setObjectName(QString::fromUtf8("actionAddFriend"));
        actionExit = new QAction(UserMainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(UserMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        usernoLabel = new QLabel(centralwidget);
        usernoLabel->setObjectName(QString::fromUtf8("usernoLabel"));
        usernoLabel->setGeometry(QRect(0, 0, 261, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("AlArabiya"));
        font.setPointSize(12);
        usernoLabel->setFont(font);
        treeWidget = new QTreeWidget(centralwidget);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(0, 40, 261, 391));
        UserMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UserMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 264, 25));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        UserMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(UserMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        UserMainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionModifyUserinfo);
        menuMenu->addAction(actionAddFriend);
        menuMenu->addAction(actionExit);

        retranslateUi(UserMainWindow);

        QMetaObject::connectSlotsByName(UserMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UserMainWindow)
    {
        UserMainWindow->setWindowTitle(QApplication::translate("UserMainWindow", "IM", 0, QApplication::UnicodeUTF8));
        actionModifyUserinfo->setText(QApplication::translate("UserMainWindow", "Modify User Info", 0, QApplication::UnicodeUTF8));
        actionAddFriend->setText(QApplication::translate("UserMainWindow", "Add Friend", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("UserMainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        usernoLabel->setText(QApplication::translate("UserMainWindow", "label", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("UserMainWindow", "contact", 0, QApplication::UnicodeUTF8));
        menuMenu->setTitle(QApplication::translate("UserMainWindow", "Menu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UserMainWindow: public Ui_UserMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMAINWINDOW_H
