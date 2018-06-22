#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QInputDialog>
#include <QMessageBox>
#include "categories.h"

namespace Ui {
class Products;
}

class Products : public QDialog
{
    Q_OBJECT

public:
    explicit Products(QWidget *parent = 0);
    ~Products();
    int tag;
    bool chosen;
    int goods_id;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::Products *ui;
    QSqlTableModel *model;
    QSqlTableModel *model_p;
};

#endif // PRODUCTS_H
