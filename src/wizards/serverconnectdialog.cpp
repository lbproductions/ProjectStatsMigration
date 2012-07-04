#include "serverconnectdialog.h"
#include "ui_serverconnectdialog.h"

#include <mainwindow/mainwindow.h>
#include <mainwindow/controller.h>
#include <model/storage.h>
#include <model/drink.h>
#include <model/drinkscontext.h>

#include <QPushButton>
#include <QElapsedTimer>

#include <LBDatabase/LBDatabase.h>

ServerConnectDialog::ServerConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerConnectDialog)
{
    ui->setupUi(this);

    m_connectButton = new QPushButton(tr("Connect"), ui->buttonBox);
    connect(m_connectButton, SIGNAL(clicked()), this, SLOT(onConnect()));
    ui->buttonBox->addButton(m_connectButton, QDialogButtonBox::ActionRole);
}

ServerConnectDialog::~ServerConnectDialog()
{
    delete ui;
}

void ServerConnectDialog::onConnect()
{
    m_remoteDriver = new LBDatabase::RestStorageDriver(QUrl("http://localhost:8080"), this);
    m_remoteDriver->init();
    connect(m_remoteDriver, SIGNAL(progress(int)), this, SLOT(progressChanged()));
    connect(m_remoteDriver, SIGNAL(finished()), this, SLOT(finished()));
}

void ServerConnectDialog::progressChanged()
{
    ui->progressBar->setMaximum(m_remoteDriver->totalRequests());
    ui->progressBar->setValue(m_remoteDriver->requestsDone());
    ui->label->setText(tr("Request %1 of %2").arg(m_remoteDriver->requestsDone()).arg(m_remoteDriver->totalRequests()));
}

void ServerConnectDialog::finished()
{
    ui->label->setText(tr("Opening storage"));
    ui->progressBar->setRange(0,0);

    MainWindow *window = new MainWindow(parentWidget());

    Storage *storage = new Storage(window);
    storage->setDriver(m_remoteDriver);

    QElapsedTimer timer;
    timer.start();
    storage->open();
    qDebug() << "Opening the storage took "+QString::number(timer.elapsed())+"ms.";

    window->controller()->openStorage(storage);
    window->show();
    accept();
}
