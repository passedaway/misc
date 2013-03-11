#include "serverinfo.h"
#include "ui_serverinfo.h"

#include "mainwindow.h"

ServerInfo::ServerInfo(QWidget *parent, MainWindow *mw) :
    QDialog(parent),
    ui(new Ui::ServerInfo)
{
    this->mw = mw;

    ui->setupUi(this);
    connect(this->ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));
    connect(this->ui->pushButtonOK, SIGNAL(clicked()), this, SLOT(on_pushButtonOK_clicked()) );

    if(mw->ip[0])
    {
	QString *ipstr = new QString(this->mw->ip);
	ui->lineEditIp->setText(*ipstr);
	delete ipstr;
    }

    if(mw->port)
    {
	QString *portstr = new QString();
	*portstr = QString::number(mw->port);
	ui->lineEditPort->setText(*portstr);
	delete portstr;
    }
}

ServerInfo::~ServerInfo()
{
    delete ui;
}

void ServerInfo::on_pushButtonOK_clicked()
{
    char *ip;
    ipbytearray = ui->lineEditIp->text().toLocal8Bit();
    ip = ipbytearray.data();

    int port_tmp = ui->lineEditPort->text().toInt();
    mw->setServerInfo(ip, (unsigned int)port_tmp);

    this->close();
    mw->show();
}

void ServerInfo::on_pushButtonCancel_clicked()
{
   this->close();
   mw->show();
}
