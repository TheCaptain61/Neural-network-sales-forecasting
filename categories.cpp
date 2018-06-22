#include "categories.h"
#include "ui_categories.h"

Categories::Categories(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Categories)
{
    ui->setupUi(this);
    tag = 0;
    chosen = false;
    model = new QSqlTableModel;
    model->setTable("categories");
    model->setSort(1, Qt::AscendingOrder);
    model->setHeaderData(0, Qt::Horizontal, tr("id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Наименование категории"));
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Categories::~Categories()
{
    delete ui;
}

void Categories::on_pushButton_clicked()
{
    bool bOk;
    QString category = QInputDialog::getText( 0,"Ввод",
                                              "Введите наименование категории: ",
                                              QLineEdit::Normal, "", &bOk);
    if (category != "" && bOk) {
        QSqlQuery query;
        query.prepare("insert into categories(name_) values (:name)");
        query.bindValue(":name", QVariant(category));
        if (!query.exec()) {
            QMessageBox::critical(this, tr("Ошибка"), query.lastError().text());
            return;
        }
        model->select();
        ui->tableView->resizeColumnsToContents();
    }
}

void Categories::on_pushButton_2_clicked()
{
    bool bOk;
    QString category = QInputDialog::getText( 0,"Ввод",
                                              "Введите наименование категории: ",
                                              QLineEdit::Normal,
                                              model->data(model->index(ui->tableView->currentIndex().row(),1)).toString(),
                                              &bOk);
    if (category != "" && bOk) {
        QSqlQuery query;
        query.prepare("update categories set name_ = :name where id = :id");
        query.bindValue(":name", QVariant(category));
        query.bindValue(":id", QVariant(model->data(model->index(ui->tableView->currentIndex().row(),0)).toInt()));
        if (!query.exec()) {
            QMessageBox::critical(this, tr("Ошибка"), query.lastError().text());
            return;
        }
        model->select();
        ui->tableView->resizeColumnsToContents();
    }
}

void Categories::on_pushButton_3_clicked()
{
    if (QMessageBox::question(this, tr("Вопрос"),
                                  tr("Вы действительно хотите удалить эту запись?"),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("delete from categories where id = :id");
        query.bindValue(":id", QVariant(model->data(model->index(ui->tableView->currentIndex().row(),0)).toInt()));
        if (!query.exec()) {
            QMessageBox::critical(this, tr("Ошибка"), query.lastError().text());
            return;
        }
        model->select();
        ui->tableView->resizeColumnsToContents();
    }

}

void Categories::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (tag = 1) {
        this->categoryId = model->data(model->index(index.row(),0)).toInt();
        chosen = true;
        this->close();
    }
}
