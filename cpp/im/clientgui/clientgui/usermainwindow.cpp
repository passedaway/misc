#include "usermainwindow.h"
#include "ui_usermainwindow.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <pthread.h>

UserMainWindow::UserMainWindow(QWidget *parent, MainWindow *mw) :
    QMainWindow(parent),
    ui(new Ui::UserMainWindow),modifyuserinfo(NULL)
{
    ui->setupUi(this);
    this->mw = mw;
	connect(ui->actionAddFriend, SIGNAL(triggered()), this, SLOT(actionAddFriendSlots()));
	connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(actionExitSlots()));
	connect(ui->actionModifyUserinfo, SIGNAL(triggered()), this, SLOT(actionModifyUserinfoSlots()));

	connect(this, SIGNAL(analyseMessageSignal(char *, QString)), this, SLOT(analyseMessageSlots(char *, QString)) );
	connect(this, SIGNAL(showInfoSignal(int, QString)), this, SLOT(showInfoSlots(int, QString)) );
	connect(this, SIGNAL(analyseCmdSignal(int)), this, SLOT(analyseCmdSlots(int)) );

	ui->treeWidget->setWindowTitle("contact");
	socket_fd = mw->socket_fd;

	userinfo = userinfo_init();
	Message *ms = ms_init(NULL, NULL, NULL);
	ms_recv_message(socket_fd, ms);

	memcpy(userinfo, ms->data + 2 * USERNO_LEN, sizeof(Userinfo));
	QString *str = new QString();
	*str = QString(userinfo->username) + "(" + QString(userinfo->userno) + ")";
	ui->usernoLabel->setText(*str);

	itemA = new QTreeWidgetItem(QStringList()<<"friend");
	itemB = new QTreeWidgetItem(QStringList()<<"stranger");
	itemC = new QTreeWidgetItem(QStringList()<<"unknown");

    ui->treeWidget->addTopLevelItem(itemA);
    ui->treeWidget->addTopLevelItem(itemB);
    ui->treeWidget->addTopLevelItem(itemC);

	fls = friendlist_init();
	int friend_num = 0;
	Friend *friend_tmp;

	do{
		ms = ms_init(NULL, NULL, NULL);
		ms_recv_message(socket_fd, ms);
		if(ms_is_ms_exit(ms))
		{
			QMessageBox::information(NULL, "ERROR", "Server has some expection!");
			this->close();
			return;
		}

		friend_num = ms->data[1] - 1;
		int i = 0;
		if(friend_num )
		{
			for(i = 0; i < friend_num; i++)
			{
            	friend_tmp = (Friend*)malloc(sizeof(Friend));
    			memcpy(friend_tmp, ms->data + 2 *USERNO_LEN + i * sizeof(Friend), sizeof(Friend));
    			friendlist_add(fls, friend_tmp);

    			QString *str_tmp = new QString();
    			*str_tmp = QString(friend_tmp->nickname) + "(" + QString(friend_tmp->userno) + ")";

    			QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(*str_tmp));
				itemA->addChild(child);
			}
		}else{
			ms_exit(ms);
			break;
		}
	}while(friend_num == ( 1014 / sizeof(Friend) + 1));

	mw->hide();

	pthread_create(&npid, NULL, runFun, (void *)this);
	is_run_net = 1;

	talklist= new TalkList();
}



UserMainWindow::~UserMainWindow()
{
    delete ui;
    userinfo_exit(userinfo);
	friendlist_exit(fls);
	delete talklist;
	this->close();
	mw->close();
}



void *UserMainWindow::runFun(void *arg)
{
	UserMainWindow *rs = (UserMainWindow *)arg;

	rs->run();
	return rs;
}

void UserMainWindow::run()
{
	Message *ms = NULL;
	while(1)
    	while(is_run_net)
    	{
    		ms =ms_init(NULL, NULL, NULL);

			ms_recv_message(socket_fd, ms);

    		analyseMessage(ms);
    		ms_exit(ms);
    	}
}

int UserMainWindow::analyseMessage(Message *ms)
{
	char dest[7] = {0};
	char src[7] = {0};
	char *info;

	if(ms_is_ms_exit(ms))
	{
		emit showInfoSignal(1, QString(""));
		is_run_net = 0;
		return 0;
	}

	memcpy(dest, ms->data, 6);
	dest[6] = 0;
	memcpy(src, ms->data + USERNO_LEN, 6);
	src[6] = 0;

	info = ms_get_info(ms);

	if( strncmp(src, "999999", 6) == 0)
	{

		if( !strcmp(info, "re-modify") )
		{
			is_run_net = 0;
			emit analyseCmdSignal(1);
    		return 0;
    	}

    	if( !strncmp(info, "add+", 4))
    	{
			emit showInfoSignal(5, QString(ms_get_info(ms)) );
    		return 0;
		}

    	if( !strncmp(info, "add_", 4))
    	{
    		//1.add_agree

    		if( !strncmp(info, "add_agree", 7) )
    		{
    			char a_userno[7];
    			char a_nickname[64];
    			char b_nickname[64];
    			Friend *fr = NULL;

    			memset(a_nickname, 0, 64);
    			memset(b_nickname, 0, 64);

    			sscanf(info, "add_agree+%s+%s+%s", a_userno, b_nickname, a_nickname);

    			memcpy(a_userno, info+strlen("add_agree+"), 6);
    			a_userno[6] = 0;

    			memcpy(b_nickname, info+strlen("add_agree+") + 7, 64);

				fr = (Friend *)malloc(sizeof(Friend));
				memset(fr, 0, sizeof(Friend));
				memcpy(fr->userno, a_userno, 6);
				memcpy(fr->nickname, b_nickname, 64);

				if(fls)
					fls = friendlist_init();

				friendlist_add(fls, fr);

				QString str_info = QString(a_userno) + " is argree your friend-requeset!";
				emit showInfoSignal(3, QString(str_info));
				return 0;
    		}

    		//2.add_disagree
    		if( !strncmp(info, "add_disagree", 7) )
    		{
    			char a_userno[7];
    			memset(a_userno, 0, 7);

    			sscanf(info, "add_disagree+%s", a_userno);

				QString str_info = QString(a_userno) + " is not agree your friend-request!";
    			emit showInfoSignal(4, QString(str_info) );
    			return 0;
    			//printf("\nWARNING:\n\t%s is not agree your friend-request!\n\n", a_userno);
    		}

    		//3.add_error
    		if( !strncmp(info, "add_error", 7) )
    		{
    			char a_userno[7];
    			memset(a_userno, 0, 7);

    			sscanf(info, "add_errore+%s", a_userno);

    			QString str_info = "friend-requeset " + QString(a_userno) + QString(info + strlen("add_error+000000"));
				emit showInfoSignal(4, QString(str_info) );
    			return 0;
    			//printf("\nWARNING:\n\tfriend-request %s error!\n\t%s\n\n", a_userno, info+strlen("add_error+000000"));

    		}

		}

    	if( !strncmp(info, "Your account in another place was second loginning, you are forced to logout!", 10) )
    	{
			emit showInfoSignal(2, QString(""));
			return  0;
    	}

		emit showInfoSignal(4, QString(ms_get_info(ms)) );
		return 0;
	}


	char *userno_name = new char[80];
	memset(userno_name, 0, 80);
	Friend *tmp = friendlist_search(fls, src);
	if(tmp == NULL)
	{
		//this message is not from friend
		//1.server

		//2.stranger

	}

	sprintf(userno_name, "%s(%s)", tmp->nickname, tmp->userno);

	QString msstr = QString(userno_name) + ":\n\t" + QString(info);

	emit analyseMessageSignal(userno_name, msstr);

	return 0;
}

void UserMainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
		QByteArray ba_userno;
		char *username_userno_p;

		QString str = item->text(column);
		ba_userno = str.toLocal8Bit();
		username_userno_p = ba_userno.data();

		talk *tmp = talklist->searchItem(username_userno_p);

		if(tmp != NULL)
		{
			tmp->show();
			return;
		}else{
			tmp = new talk(0, username_userno_p, this);
			tmp->show();
			talklist->addItem(tmp);
		}
}

void UserMainWindow::actionAddFriendSlots()
{
	addfriend = new AddFriend(0, this);
	addfriend->show();
}

void UserMainWindow::actionExitSlots()
{
	if(socket_fd)
	{
		socket_close(socket_fd);
		socket_fd = 0;
		mw->socket_fd = 0;
	}
	this->close();
	mw->close();
}

void UserMainWindow::actionModifyUserinfoSlots()
{
	ms_send_message_to_server(this->socket_fd, (char*)"modify");
}


void UserMainWindow::analyseMessageSlots(char *userno_name, QString msstr)
{
	talk *talk_tmp = talklist->searchItem(userno_name);
	if(talk_tmp == NULL)
	{
		talk_tmp = new talk(0, userno_name, this);
		talk_tmp->show();
		talklist->addItem(talk_tmp);
	}else{
		talk_tmp->show();
	}

	talk_tmp->addList(msstr);
}

void UserMainWindow::analyseCmdSlots(int op)
{
	switch(op)
	{
		case 1:
			//modify user info
			modifyuserinfo = new ModifyUserinfo(0, this);
			modifyuserinfo->show();
			this->hide();
			break;
		case 2:
			//add friend
			break;
	}
}

void UserMainWindow::showInfoSlots(int op, QString str)
{
	switch(op)
	{
		case 1:
			is_run_net = 0;
			socket_close(socket_fd);
			socket_fd = 0;
			this->close();
			mw->show();
			QMessageBox::information(NULL, "Error", "Server has some expection!");
			break;
		case 2:
			mw->show();
			QMessageBox::information(NULL, "WARNING", "Your account in another place was second loginning, you are forced to logout!\nplease restart the program, then re-login!\n\n");
			this->close();
			is_run_net = 0;
			break;
		case 3:
		//add success
		{
			QByteArray ba = str.toLocal8Bit();
			char *str_p = ba.data();
			Friend *friend_tmp = friendlist_search(fls, str_p);

			QString *str_tmp = new QString();
			*str_tmp = QString(friend_tmp->nickname) + "(" + QString(friend_tmp->userno) + ")";

			QTreeWidgetItem *tmp_child = new QTreeWidgetItem(QStringList(*str_tmp));
			itemA->addChild(tmp_child);

			ui->treeWidget->update();

			QMessageBox::information(NULL, "WARNING", str);
		}
			break;
		case 4:
		//show info
			QMessageBox::information(NULL, "WARNING", str);
			break;
		case 5:
			//add friend requeset
			addfriendreply = new AddFriendReply(0, this, str);
			addfriendreply->show();
			break;
	}
}

void UserMainWindow::setLabelText(QString str)
{
	ui->usernoLabel->setText(str);
}
