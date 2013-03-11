#include "talk.h"
#include "ui_talk.h"
#include "message.h"
#include "usermainwindow.h"

#include <QMessageBox>

talk::talk(QWidget *parent, char *username_userno, UserMainWindow *umw) :
    QDialog(parent),
    ui(new Ui::talk)
{
	this->umw = umw;
	ui->setupUi(this);
	QString title = "talk with  " + QString(username_userno);
	setWindowTitle(QString(title));

	this->username_userno = new char[strlen(username_userno) + 1];
	memset(this->username_userno, 0, strlen(username_userno) + 1);
	strcpy(this->username_userno, username_userno);

	memcpy(this->friend_userno, this->username_userno+strlen(this->username_userno) - 7,  6);
	this->friend_userno[6] = 0;

}

talk::~talk()
{
	delete ui;
	delete []username_userno;
}

void talk::addList(QString &str)
{
	ui->listWidget->addItem(str);
}

void talk::on_pushButtonClose_clicked()
{
   this->close();
}

void talk::on_pushButtonSend_clicked()
{
   //send messge to server
	QString text = ui->textEdit->toPlainText();

	if(text.isEmpty())
	{
		QMessageBox::information(NULL, "WARNING", "Message can not empty!");
		return;
	}

	batext = text.toLocal8Bit();
	char *info = batext.data();

	Message *ms = ms_init(this->friend_userno, umw->userinfo->userno, NULL);
	memcpy(ms->data + 2*USERNO_LEN, info, strlen(info));

	ms_send_message(umw->socket_fd, ms);

	//paste messge on the listWidget
	ui->textEdit->clear();

	QString stext = QString(umw->userinfo->username) + "(" + QString(umw->userinfo->userno) + "):\n\t" + text;
	ui->listWidget->addItem(stext);
}
