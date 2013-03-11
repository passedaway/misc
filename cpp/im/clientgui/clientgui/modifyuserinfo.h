#ifndef MODIFYUSERINFO_H
#define MODIFYUSERINFO_H

#include <QDialog>

#include "userinfo.h"

namespace Ui {
    class ModifyUserinfo;
}
class UserMainWindow;

class ModifyUserinfo : public QDialog
{
    Q_OBJECT

public:
	explicit ModifyUserinfo(QWidget *parent = 0, UserMainWindow *umw = 0);
    ~ModifyUserinfo();

private slots:
	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

private:
	Ui::ModifyUserinfo *ui;
	UserMainWindow *umw;

    int socket_fd;
    Userinfo *userinfo;

    char modify_userno[7];

    QByteArray bytea_username;
    QByteArray bytea_passwd;
    QByteArray bytea_passwd2;
    QByteArray bytea_name;
    QByteArray bytea_sex;
    QByteArray bytea_emaile;
};

#endif // MODIFYUSERINFO_H
