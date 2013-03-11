#include "mainwindow.h"
#include "ui_mainwindow.h"
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(gotoView(int)), this, SLOT(gotoViewSlots(int)));
    connect(this->ui->actionSet_server, SIGNAL(triggered()), this, SLOT(setServerSlots()));
    connect(this->ui->actionApply_id, SIGNAL(triggered()), this, SLOT(applyidSlots()));

    ip = new char[20];
    memset(ip, 0, 20);
    strcpy(ip, "192.168.1.120");

    port = 8800;

    socket_fd = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete []ip;
}

void MainWindow::on_login_clicked()
{
    QString str_userno = ui->lineEditUserno->text();

    QString *info;
    if(!str_userno.length())
    {
        info = new QString("please input userno!");
        QMessageBox::information(NULL, "login", *info);
        delete info;
        return;
    }else if( str_userno.length() != 6){
        info = new QString("check userno!");
        QMessageBox::information(NULL, "login", *info);
        delete info;
        return;
    }

    QString str_passwd = ui->lineEditPasswd->text();
    if(!str_passwd.length())
     {
         info = new QString("please input password!");
         QMessageBox::information(NULL, "login", *info);
         delete info;
         return;
     }

   // QString inputinfo = str_userno + str_passwd;
	//QMessageBox::information(NULL, "login", inputinfo);


	int loginflag = login();

	if(loginflag == 1)
	{
		//login success
		emit gotoView(3);
	}else if( -1 == loginflag){
		//server wrong
		QMessageBox::information(NULL, "ERROR", "cannot connect with server!Check server information!");
	}else if( -2 == loginflag){
		//user or userno wrong
		QMessageBox::information(NULL, "ERROR", "Userno and password is not match!");
	}
}


//л
void MainWindow::gotoViewSlots(int op)
{
    switch(op)
    {
    case 1:
        //show set server view
		serverinfo = new ServerInfo(0, this);
    	serverinfo->show();
		this->hide();
        break;
    case 2:
	//show apply id view
		applyid = new ApplyId(0, this);
		applyid->show();
//		this->hide();
		break;

    case 3:
		//show login success the userinfo view
		usermainwindow = new UserMainWindow(0, this);
		usermainwindow->show();
		//this->hide();
		break;
    }
}


//÷Ϣ
void MainWindow::setServerSlots()
{
    emit gotoView(1);
}

//û¼ɹʱ
void MainWindow::applyidSlots()
{
    emit gotoView(2);
}

//û¼ɹʱ
void MainWindow::userViewSlots()
{
    emit gotoView(3);
}



void MainWindow::on_quit_clicked()
{
    this->close();
}

void MainWindow::setServerInfo(char *ip, unsigned int port)
{
    if(this->ip)
    {
	memset(this->ip, 0, 20);
	strcpy(this->ip, ip);
    }

    if(port)
	this->port = port;
    else
	this->port = 8800;
}


int MainWindow::login()
{
	socket_fd = socket_init(ip, port);

	if(!socket_fd)
	{
		return -1;
	}

	ms_send_message_to_server(socket_fd, (char *)"login");

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
		return -1;
	}

	if( strcmp(ms_get_info(ms), (char *)"re-login") )
	{
		//server not reply "re-login"
		QMessageBox::information(NULL, "ERROR", "Server has some expection!");
		socket_close(socket_fd);
		socket_fd = 0;
		ms_exit(ms);
		return -1;
	}

	ms_exit(ms);

	bytea_userno = ui->lineEditUserno->text().toLocal8Bit();
	char *userno_p = bytea_userno.data();

	bytea_passwd = ui->lineEditPasswd->text().toLocal8Bit();
	char *passwd_p = bytea_passwd.data();

	ms = ms_init((char *)"999999", userno_p, passwd_p);
	ms_send_message(socket_fd, ms);
	ms_exit(ms);

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
		return -1;
	}

	if( strncmp(ms_get_info(ms), "login_success", strlen("login_success")) == 0 )
	{
		return 1;
	}else{
		return -2;
	}
}
