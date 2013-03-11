#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include "message.h"
#include "userinfo.h"
#include "friendlist.h"
#include "talk.h"
#include "talklist.h"
#include "modifyuserinfo.h"
#include "addfriend.h"
#include "addfriendreply.h"

class MainWindow;

namespace Ui {
    class UserMainWindow;
}

class UserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserMainWindow(QWidget *parent = 0, MainWindow *mw = 0);
    ~UserMainWindow();

private slots:
	void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
	void actionModifyUserinfoSlots();
	void actionExitSlots();
	void actionAddFriendSlots();
	void analyseMessageSlots(char *username_userno_p, QString msstr);
	void showInfoSlots(int op, QString str);
	void analyseCmdSlots(int op);
signals:
	void analyseCmdSignal(int op);
	void analyseMessageSignal(char *username_userno_p, QString msstr);
	void showInfoSignal(int op, QString str);


public:
	Ui::UserMainWindow *ui;

	MainWindow *mw;
	ModifyUserinfo *modifyuserinfo;
	AddFriend *addfriend;
	AddFriendReply *addfriendreply;

    QTreeWidgetItem *itemA;
    QTreeWidgetItem *itemB;
    QTreeWidgetItem *itemC;

	TalkList *talklist;

	pthread_t npid;


	static void *runFun(void *arg);
	void run();

	int analyseMessage(Message *ms);

public:
	int is_run_net;
	int socket_fd;
	Userinfo *userinfo;
	FriendList *fls;

	void setLabelText(QString);
};

#endif // USERMAINWINDOW_H
