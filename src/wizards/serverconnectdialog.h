#ifndef SERVERCONNECTDIALOG_H
#define SERVERCONNECTDIALOG_H

#include <QDialog>

namespace LBDatabase {
class RestStorageDriver;
}

namespace Ui {
class ServerConnectDialog;
}

class ServerConnectDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ServerConnectDialog(QWidget *parent = 0);
    ~ServerConnectDialog();
    
private slots:
    void onConnect();
    void progressChanged();
    void finished();

private:
    Ui::ServerConnectDialog *ui;

    QPushButton *m_connectButton;
    LBDatabase::RestStorageDriver *m_remoteDriver;
};

#endif // SERVERCONNECTDIALOG_H
