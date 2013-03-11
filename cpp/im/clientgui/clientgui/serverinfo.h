#ifndef SERVERINFO_H
#define SERVERINFO_H

#include <QDialog>

class MainWindow;

namespace Ui {
    class ServerInfo;
}


class ServerInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ServerInfo(QWidget *parent = 0, MainWindow *mw = 0);
    ~ServerInfo();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

public:
    Ui::ServerInfo *ui;

    MainWindow  *mw;

    QByteArray ipbytearray;
};

#endif // SERVERINFO_H
