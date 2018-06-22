#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    authorized = false;
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(ui->host->text());
    db.setDatabaseName(ui->database->text());
    db.setUserName(ui->login->text());
    db.setPassword(ui->pwd->text());
    if (!db.open()) {
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),"Ошибка при подключении к базе данных:\n"+
                              db.lastError().text());
        this->authorized = false;
        return;
    }
    authorized = true;
    this->close();
}
