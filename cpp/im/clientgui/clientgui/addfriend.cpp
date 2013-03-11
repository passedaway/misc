#include "addfriend.h"
#include "ui_addfriend.h"

#include "usermainwindow.h"
#include "message.h"
#include "userinfo.h"

#include <QMessageBox>

AddFriend::AddFriend(QWidget *parent, UserMainWindow *umw) :
    QDialog(parent),
    ui(new Ui::AddFriend)
{
	this->umw = umw;
	this->socket_fd = umw->socket_fd;
    ui->setupUi(this);
}

AddFriend::~AddFriend()
{
    delete ui;
}

void AddFriend::on_pushButtonOk_clicked()
{
	QByteArray ba_userno;
	QByteArray ba_nickname;

	ba_userno = ui->lineEditUserno->text().toLocal8Bit();
	char *userno_p = ba_userno.data();

	ba_nickname = ui->lineEditNickname->text().toLocal8Bit();
	char *nickname_p = ba_nickname.data();

	if( !userinfo_checkUserno(userno_p) )
	{
		//userno wrong
		QMessageBox::information(NULL, "WARNING", "userno is nor format!");
		return;
	}

	//make message as add+userno+nickname
	char *buf = new char[256];
	memset(buf, 0, 256);

	sprintf(buf, "add+%s+%s", userno_p, nickname_p);

	//then send to server
	ms_send_message_to_server(socket_fd, buf);
	delete []buf;
	QMessageBox::information(NULL, "Info", "your applycation send to server!");
	this->close();
}

void AddFriend::on_pushButtonCancel_clicked()
{
	this->close();
}
