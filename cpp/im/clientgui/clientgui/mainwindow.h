#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "serverinfo.h"
#include "applyid.h"
#include "usermainwindow.h"
#include "message.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_login_clicked();
  void on_quit_clicked();

    //л
    void gotoViewSlots(int);
    //÷Ϣ
    void setServerSlots();
    //û˺ʱ
    void applyidSlots();
    //û¼ɹʱ
    void userViewSlots();



signals:
    void gotoView(int);

private:
    Ui::MainWindow *ui;

    ServerInfo *serverinfo;
    ApplyId *applyid;
    UserMainWindow *usermainwindow;

	QByteArray bytea_userno;
	QByteArray bytea_passwd;
public:
	int socket_fd;
    char *ip;//server ip
    unsigned int port;//server port
     //set server info
    void setServerInfo(char *ip,  unsigned int port);

    int login();
};

#endif // MAINWINDOW_H
