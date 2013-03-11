#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QDialog>

class UserMainWindow;

namespace Ui {
    class AddFriend;
}

class AddFriend : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriend(QWidget *parent = 0, UserMainWindow *umw = 0);
    ~AddFriend();

private slots:
	void on_pushButtonOk_clicked();

	void on_pushButtonCancel_clicked();

private:
    Ui::AddFriend *ui;

	UserMainWindow *umw;
    int socket_fd;
};

#endif // ADDFRIEND_H
