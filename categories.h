#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QInputDialog>
#include <QMessageBox>

namespace Ui {
class Categories;
}

class Categories : public QDialog
{
    Q_OBJECT

public:
    explicit Categories(QWidget *parent = 0);
    ~Categories();
    int tag;
    int categoryId;
    bool chosen;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    QSqlTableModel *model;
    Ui::Categories *ui;
};

#endif // CATEGORIES_H
