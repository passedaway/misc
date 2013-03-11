#include "applyid.h"
#include "ui_applyid.h"
#include "mainwindow.h"

#include "userinfo.h"
#include "message.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>

#include <QMessageBox>


ApplyId::ApplyId(QWidget *parent, MainWindow *mw) :
    QDialog(parent),
    ui(new Ui::ApplyId)
{

	ui->setupUi(this);
	//apply id stage 1 & stage 2

	socket_fd = socket_init(mw->ip, mw->port);
	if(socket_fd == 0)
	{
		//connect server error
		QMessageBox::information(NULL, "Error", "can not connect with server!\n Check server infomation");
		this->close();
	    return;
	}

	ui->statusLabel->setText(QString("Connect server success!"));

	ms_send_message_to_server(socket_fd, (char *)"apply");

	Message *ms = ms_init(NULL, NULL, NULL);
	ms_recv_message(socket_fd, ms);
	if( ms_is_ms_exit(ms) )
	{
		char *buf = new char[256];
		memset(buf, 0, 256);
		sprintf(buf, "\tSorry about this.\nThe Server has some exceptions, and disconnection to the client!\nPlease restart the client,and try agian!");
		QMessageBox::information(NULL, "ERROR", "Server has some expection!");
		delete buf;

		ms_exit(ms);
		this->close();
		return;
	}

	if( strcmp(ms_get_info(ms), (char *)"re-apply") )
	{
		//server not reply "re-apply"
		ui->statusLabel->setText(QString("server has some expection!"));
		socket_close(socket_fd);
		socket_fd = 0;
		ms_exit(ms);

		//mw->show();
		this->close();
		return;
	}

	ms_exit(ms);
	//stage 3
	ms_send_message_to_server(socket_fd, (char *)"start");

	ms = ms_init(NULL, NULL, NULL);
	ms_recv_message(socket_fd, ms);
	if( ms_is_ms_exit(ms) )
	{
		char *buf = new char[256];
		memset(buf, 0, 256);
		sprintf(buf, "\tSorry about this.\nThe Server has some exceptions, and disconnection to the client!\nPlease restart the client,and try agian!");
		QMessageBox::information(NULL, "ERROR", "Server has some expection!");
		delete buf;

		ms_exit(ms);
		return;
	}

	memset(apply_userno, 0, 7);
	memcpy(apply_userno, ms_get_info(ms), 6);

	ms_exit(ms);

	if( !userinfo_checkUserno(apply_userno) )
	{
		ui->statusLabel->setText(QString("apply id wrong!Try again!Close this and try again"));
		socket_close(socket_fd);
		socket_fd = 0;
		this->close();
		return;
	}
	else
	{
		ui->userno->setText(QString(apply_userno));
		ui->statusLabel->setText(QString("Fill infomation"));
	//	mw->hide();
	//	this->show();
	}
}

ApplyId::~ApplyId()
{
    delete ui;
}

void ApplyId::on_pushButtonCancel_clicked()
{
	socket_close(socket_fd);
	socket_fd = 0;

	this->close();
	//mw->show();
}

void ApplyId::on_pushButtonCommit_clicked()
{
   //apply id
	if( ! socket_fd)
   	{
   		//dis connect with the server

   		//show Infomation
		QMessageBox::information(NULL, "ERROR", "Server has some expection!");

   		//close this dialog
		this->close();
		//mw->show();
   		return;
	}

	bytea_username = ui->lineEditUsername->text().toLocal8Bit();
	char *username_p = bytea_username.data();

	bytea_passwd = ui->lineEditPasswd->text().toLocal8Bit();
	char *passwd_p = bytea_passwd.data();

	bytea_passwd2 = ui->lineEditPasswd2->text().toLocal8Bit();
	char *passwd2_p = bytea_passwd2.data();

	bytea_name = ui->lineEditName->text().toLocal8Bit();
	char *name_p = bytea_name.data();

	//get sex
	bytea_sex = ui->comboBoxSex->currentText().toLocal8Bit();
	char *sex_p = bytea_sex.data();

	bytea_emaile = ui->lineEditEmaile->text().toLocal8Bit();
	char *emaile_p = bytea_emaile.data();

	//check passwd
   	if(strcmp(passwd_p, passwd2_p))
    {
		QMessageBox::information(NULL, "Error", "The two password input didnot same!Input again!");
		return;
	}else{
		if( !userinfo_checkPasswd(passwd_p))
		{
			QMessageBox::information(NULL, "Error", "password length 6-32! Input again!");
			return;
		}
	}

	//check emaile
	if ( !userinfo_checkEmaile(emaile_p) )
	{
		//emaile illegal
		QMessageBox::information(NULL, "Error", "Check emaile format!");
		return;
	}


	Userinfo *user = userinfo_init();
	userinfo_ioctl(user, SET_USERNO, (void*)apply_userno);
	userinfo_ioctl(user, SET_USERNAME, (void*)username_p);
	userinfo_ioctl(user, SET_PASSWD, (void*)passwd_p);
	userinfo_ioctl(user, SET_NAME, (void*)name_p);
	userinfo_ioctl(user, SET_SEX,  (void*)sex_p);
	userinfo_ioctl(user, SET_EMAILE, (void*)emaile_p);

	Message *ms = ms_init((char *)"999999", (char *)"000000", NULL);
	memcpy(ms->data+2*USERNO_LEN, user,  sizeof(Userinfo));

	ms_send_message(socket_fd, ms);

	ms_exit(ms);
	userinfo_exit(user);
	socket_close(socket_fd);
	socket_fd = 0;

	/*
	char *buf = new char[256];
	memset(buf, 0, 256);
	sprintf(buf, "Your userno : %s\n password : %s\n!You can login now!", apply_userno, passwd_p);
	QMessageBox::information(NULL, "Success", QString(buf));
//	delete []buf;
*/

//	mw->show();
	this->close();
}
