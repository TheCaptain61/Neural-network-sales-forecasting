#include "products.h"
#include "ui_products.h"

Products::Products(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Products)
{
    ui->setupUi(this);
    tag = 0;
    chosen = false;
    model = new QSqlTableModel;
    model->setTable("view_goods");
    model->setSort(1, Qt::AscendingOrder);
    model->setHeaderData(0, Qt::Horizontal, tr("id"));
    model->setHeaderData(1, Qt::Horizontal, tr("Наименование товара"));
    model->setHeaderData(2, Qt::Horizontal, tr("Наименование категории"));
    model->setHeaderData(3, Qt::Horizontal, tr("ид категории"));
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setColumnHidden(3, true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    model_p = new QSqlTableModel;
    model_p->setTable("view_prices");
    model_p->setHeaderData(0, Qt::Horizontal, tr("id"));
    model_p->setHeaderData(1, Qt::Horizontal, tr("Цена, руб."));
    model_p->setHeaderData(2, Qt::Horizontal, tr("ид товара"));
    model_p->setHeaderData(3, Qt::Horizontal, tr("Дата установки цены"));
    model_p->setFilter("goods_id = "+model->data(model->index(ui->tableView->currentIndex().row(),0)).toString());
    model_p->select();


    ui->tableView_2->setModel(model_p);
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setColumnHidden(0, true);
    ui->tableView_2->setColumnHidden(2, true);
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Products::~Products()
{
    delete ui;
}

void Products::on_pushButton_clicked()
{
    Categories *form = new Categories(this);
    form->setModal(true);
    form->tag = 1;
    form->exec();
    if (form->chosen) {
        bool bOk;
        QString name_ = QInputDialog::getText( 0,"Ввод",
                                               "Введите наименование товара: ",
                                               QLineEdit::Normal, "", &bOk);
        if (name_ != "" && bOk) {

            QSqlQuery query;
            query.prepare("insert into goods(name_, category_id) "
                          "values (:name, :catId)");
            query.bindValue(":name", QVariant(name_));
            query.bindValue(":catId", QVariant(form->categoryId));

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

void Products::on_pushButton_2_clicked()
{
    bool bOk;
    QString name_ = QInputDialog::getText( 0,"Ввод",
                                           "Введите наименование товара: ",
                                           QLineEdit::Normal,
                                           model->data(model->index(ui->tableView->currentIndex().row(),1)).toString(), &bOk);
    if (name_ != "" && bOk) {

        QSqlQuery query;
        query.prepare("update goods set name_ = :name "
                      "where id = :id");
        query.bindValue(":name", QVariant(name_));
        query.bindValue(":id", QVariant(model->data(model->index(ui->tableView->currentIndex().row(),0)).toInt()));
        if (!query.exec()) {
            QMessageBox::critical(this, tr("Ошибка"), query.lastError().text());
            return;
        }
        model->select();
        ui->tableView->resizeColumnsToContents();
    }


}

void Products::on_pushButton_3_clicked()
{
    if (QMessageBox::question(this, tr("Вопрос"),
                                  tr("Вы действительно хотите удалить эту запись?"),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("delete from goods where id = :id");
        query.bindValue(":id", QVariant(model->data(model->index(ui->tableView->currentIndex().row(),0)).toInt()));
        if (!query.exec()) {
            QMessageBox::critical(this, tr("Ошибка"), query.lastError().text());
            return;
        }
        model->select();
        ui->tableView->resizeColumnsToContents();
    }
}

void Products::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (tag == 1) {
        goods_id = model->data(model->index(index.row(),0)).toInt();
        chosen = true;
        this->close();
    }
}

void Products::on_pushButton_4_clicked()
{
    bool bOk;
    int price = QInputDialog::getDouble(0, "Ввод",
                                      "Введите количество шт.:",
                                      1,
                                      1, 10000000, 1,&bOk);
    if (price > 0 && bOk) {
        QSqlQuery query;
        query.prepare("insert into prices(goods_id, price) "
                      "values (:goods_id, :price)");
        query.bindValue(":goods_id", QVariant(model->data(model->index(ui->tableView->currentIndex().row(),0)).toInt()));
        query.bindValue(":price", QVariant(price));
        if (!query.exec()) {
            QMessageBox::critical(this, tr("Ошибка"), query.lastError().text());
            return;
        }
        model_p->select();
        ui->tableView_2->resizeColumnsToContents();

    }
}

void Products::on_tableView_clicked(const QModelIndex &index)
{
    model_p->setFilter("goods_id = "+model->data(model->index(index.row(),0)).toString());
    model_p->select();
}
