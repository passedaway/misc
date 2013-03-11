#include "addfriendreply.h"
#include "ui_addfriendreply.h"
#include "message.h"
#include "userinfo.h"

#include "usermainwindow.h"

AddFriendReply::AddFriendReply(QWidget *parent, UserMainWindow *umw, QString qstr) :
    QDialog(parent),
    ui(new Ui::AddFriendReply)
{
	this->umw = umw;
	this->socket_fd = umw->socket_fd;
	ui->setupUi(this);

	QByteArray ba_str = qstr.toLocal8Bit();
	char *info = ba_str.data();



	memcpy(a_userno, info + 4, 6);
	a_userno[6] = 0;

	memset(b_nickname, 0, 64);
	memcpy(b_nickname, info + 11, 64);

	QString status_str = "accept one friend(" + QString(a_userno) + ") requeset";

	ui->statusLabel->setText(status_str);
}

AddFriendReply::~AddFriendReply()
{
    delete ui;
}

void AddFriendReply::on_pushButtonAgree_clicked()
{
	char req_info[256];
	memset(req_info, 0, 256);

	QByteArray ba_nickname = ui->lineEdit->text().toLocal8Bit();
	char *aa_nickname = ba_nickname.data();

	strcpy(req_info, "add_agree+");
	strcpy(req_info+10, a_userno);
	req_info[10+6] = '+';
	memcpy(req_info+17, b_nickname, 64);
	req_info[17+64] = '+';
	strcpy(req_info+17+65, aa_nickname);

	Message *req_ms = ms_init((char *)"999999", umw->userinfo->userno, NULL);
	memcpy(req_ms->data+2*USERNO_LEN, req_info, 256);

	ms_send_message(socket_fd, req_ms);
	ms_exit(req_ms);

	QString *str_tmp = new QString();
	*str_tmp = QString(aa_nickname) + "(" + QString(a_userno) + ")";

	QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(*str_tmp));
	umw->itemA->addChild(child);

	Friend *friend_tmp = (Friend*)malloc(sizeof(Friend));
	memcpy(friend_tmp->userno, a_userno, 7);
	memset(friend_tmp->nickname, 0, 57);
	strcpy(friend_tmp->nickname, aa_nickname);

    friendlist_add(umw->fls, friend_tmp);

	this->close();
}

void AddFriendReply::on_pushButtonDisagree_clicked()
{
	char req_info[256];

	Message *ms = ms_init( (char *)"999999", umw->userinfo->userno, NULL);

	memset(req_info, 0, 256);
	sprintf(req_info, "add_disagree+%s", a_userno);
	memcpy(ms->data+2*USERNO_LEN, req_info, strlen(req_info));

	ms_send_message(socket_fd, ms);
	ms_exit(ms);

	this->close();
}
