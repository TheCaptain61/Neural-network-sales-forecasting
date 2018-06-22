#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ConnectionDialog *form = new ConnectionDialog();
    form->setModal(true);
    form->exec();
    this->authorized = form->authorized;
    if (!authorized)
        qApp->quit();

    this->showMaximized();
    model = new QSqlTableModel;
    model->setTable("view_selling");
    model->setHeaderData(0, Qt::Horizontal, tr("Дата и время"));
    model->setHeaderData(1, Qt::Horizontal, tr("Товар"));
    model->setHeaderData(2, Qt::Horizontal, tr("Категория"));
    model->setHeaderData(3, Qt::Horizontal, tr("Количество"));
    model->setHeaderData(4, Qt::Horizontal, tr("Стоимость, руб."));
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setColumnHidden(5, true);
    ui->tableView->setColumnHidden(6, true);
    ui->tableView->setColumnHidden(7, true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionGthtqnb_triggered()
{
    Prolong *form = new Prolong(this);
    form->setModal(true);
    form->exec();
    delete form;
}

void MainWindow::on_action_triggered()
{
    Categories *form = new Categories(this);
    form->setModal(true);
    form->exec();
    delete form;
}

void MainWindow::on_action_2_triggered()
{
    Products *form = new Products(this);
    form->setModal(true);
    form->exec();
    delete form;
}

void MainWindow::on_pushButton_clicked()
{
    Products *form = new Products(this);
    form->setModal(true);
    form->tag = 1;
    form->exec();
    if (form->chosen) {
        bool bOk;
        int amount = QInputDialog::getInt(0, "Ввод",
                                          "Введите количество шт.:",
                                          1,
                                          1, 10000, 1,&bOk);
        if (amount > 0 && bOk) {
            QSqlQuery query;
            query.prepare("select change_selling(:goods_id, :amount, :date_, 0)");
            query.bindValue(":goods_id", QVariant(form->goods_id));
            query.bindValue(":amount", QVariant(amount));
            query.bindValue(":date_", QVariant(QDateTime::currentDateTime()));
            if (!query.exec()) {
                QMessageBox::critical(this, tr("Ошибка"), query.lastError().text());
                return;
            }
            model->select();
            ui->tableView->resizeColumnsToContents();
        }
    }
    delete form;
}

void MainWindow::on_pushButton_2_clicked()
{
    bool bOk;
    int amount = QInputDialog::getInt(0, "Ввод",
                                      "Введите количество шт.:",
                                      model->data(model->index(ui->tableView->currentIndex().row(),3)).toInt(),
                                      1, 10000, 1,&bOk);
    if (amount > 0 && bOk) {
        QSqlQuery query;
        query.prepare("select change_selling(:goods_id, :amount, :date_, :id)");
        query.bindValue(":goods_id", QVariant(model->data(model->index(ui->tableView->currentIndex().row(),6)).toInt()));
        query.bindValue(":amount", QVariant(amount));
        query.bindValue(":date_", QVariant(model->data(model->index(ui->tableView->currentIndex().row(),0)).toDateTime()));
        query.bindValue(":id", QVariant(model->data(model->index(ui->tableView->currentIndex().row(),5)).toInt()));
        if (!query.exec()) {
            QMessageBox::critical(this, tr("Ошибка"), query.lastError().text());
            return;
        }
        model->select();
        ui->tableView->resizeColumnsToContents();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if (QMessageBox::question(this, tr("Вопрос"),
                                  tr("Вы действительно хотите удалить эту запись?"),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("delete from sellings where id = :id");
        query.bindValue(":id", QVariant(model->data(model->index(ui->tableView->currentIndex().row(),5)).toInt()));
        if (!query.exec()) {
            QMessageBox::critical(this, tr("Ошибка"), query.lastError().text());
            return;
        }
        model->select();
        ui->tableView->resizeColumnsToContents();
    }
}
