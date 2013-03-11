#include "modifyuserinfo.h"
#include "ui_modifyuserinfo.h"
#include "message.h"
#include "usermainwindow.h"

#include <QMessageBox>

ModifyUserinfo::ModifyUserinfo(QWidget *parent, UserMainWindow *umw) :
    QDialog(parent),
    ui(new Ui::ModifyUserinfo)
{
	this->umw = umw;
	this->socket_fd = umw->socket_fd;

    ui->setupUi(this);

	Message *ms = ms_init(NULL, NULL, NULL);
	ms_recv_message(socket_fd, ms);

	userinfo = userinfo_init();

	memcpy(userinfo, ms_get_info(ms), sizeof(Userinfo));
	ms_exit(ms);

	memcpy(modify_userno, userinfo, 6);
	modify_userno[6] = 0;

	ui->labelUserno->setText( QString(userinfo->userno) );
	ui->lineEditPasswd->setText( QString(userinfo->passwd) );
	ui->lineEditUsername->setText( QString(userinfo->username) );
	ui->lineEditName->setText( QString(userinfo->name) );
	ui->lineEditEmaile->setText( QString(userinfo->emaile) );

	if( !strcmp(userinfo->sex, (char *)"female") )
	{
		ui->comboBoxSex->setCurrentIndex(1);
	}else{
		ui->comboBoxSex->setCurrentIndex(0);
	}
}

ModifyUserinfo::~ModifyUserinfo()
{
	userinfo_exit(userinfo);
    delete ui;
    umw->show();
	umw->is_run_net = 1;
}

void ModifyUserinfo::on_pushButton_clicked()
{
	//get info from ui
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

	memset(userinfo, 0, sizeof(Userinfo) );
	userinfo_ioctl(userinfo, SET_USERNO, (void*)modify_userno);
	userinfo_ioctl(userinfo, SET_USERNAME, (void*)username_p);
	userinfo_ioctl(userinfo, SET_PASSWD, (void*)passwd_p);
	userinfo_ioctl(userinfo, SET_NAME, (void*)name_p);
	userinfo_ioctl(userinfo, SET_SEX,  (void*)sex_p);
	userinfo_ioctl(userinfo, SET_EMAILE, (void*)emaile_p);

	//commit
	Message *ms = ms_init((char *)"999999", (char *)"000000", NULL);
	memcpy(ms->data + 12, userinfo, sizeof(Userinfo));
	ms_send_message(socket_fd, ms);
	ms_exit(ms);

	memcpy(umw->userinfo, userinfo, sizeof(Userinfo));
	umw->show();

	QString userno_string = QString(userinfo->username) + "(" + QString(userinfo->userno) +")";
	umw->setLabelText(userno_string);
	umw->is_run_net = 1;
	userinfo_exit(userinfo);
	this->close();
}

void ModifyUserinfo::on_pushButton_2_clicked()
{
	//cancel

	Message *ms = ms_init((char *)"999999", (char *)"000000", NULL);

	memcpy(ms->data + 12, userinfo, sizeof(Userinfo));

	ms_send_message(socket_fd, ms);
	ms_exit(ms);

	userinfo_exit(userinfo);

	umw->show();
	umw->is_run_net = 1;
	this->close();
}
