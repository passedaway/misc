#ifndef APPLYID_H
#define APPLYID_H

#include <QDialog>
#include "message.h"

class MainWindow;


namespace Ui {
    class ApplyId;
}

class ApplyId : public QDialog
{
    Q_OBJECT

public:
    explicit ApplyId(QWidget *parent = 0, MainWindow *mw = 0);
    ~ApplyId();

private slots:

	void on_pushButtonCancel_clicked();

	void on_pushButtonCommit_clicked();

private:
    Ui::ApplyId *ui;

    MainWindow *mw;

    int socket_fd;

    char apply_userno[7];

    QByteArray bytea_username;
    QByteArray bytea_passwd;
    QByteArray bytea_passwd2;
    QByteArray bytea_name;
    QByteArray bytea_sex;
    QByteArray bytea_emaile;
};

#endif // APPLYID_H
