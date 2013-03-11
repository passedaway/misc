#ifndef TALK_H
#define TALK_H

#include <QDialog>

class UserMainWindow;
namespace Ui {
    class talk;
}

class talk : public QDialog
{
    Q_OBJECT

public:
	explicit talk(QWidget *parent = 0, char *username_userno = NULL, UserMainWindow *umw = 0);
	~talk();

	void addList(QString &str);

private:
	Ui::talk *ui;
	UserMainWindow *umw;

	QByteArray batext;

public:
	talk *next;
	char *username_userno;
	char friend_userno[7];
private slots:
	void on_pushButtonClose_clicked();
	void on_pushButtonSend_clicked();
};

#endif // TALK_H
