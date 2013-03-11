#ifndef ADDFRIENDREPLY_H
#define ADDFRIENDREPLY_H

#include <QDialog>

namespace Ui {
    class AddFriendReply;
}
class UserMainWindow;

class AddFriendReply : public QDialog
{
    Q_OBJECT

public:
	explicit AddFriendReply(QWidget *parent = 0, UserMainWindow *umw = 0, QString qstr = "0");
    ~AddFriendReply();

private slots:
	void on_pushButtonAgree_clicked();

	void on_pushButtonDisagree_clicked();

private:
	Ui::AddFriendReply *ui;

	UserMainWindow *umw;
	int socket_fd;

	char a_userno[7];
    char b_nickname[64];
	char a_nickname[64];
};

#endif // ADDFRIENDREPLY_H
