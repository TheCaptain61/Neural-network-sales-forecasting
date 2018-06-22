#ifndef PROLONG_H
#define PROLONG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <vector>
#include <QVariant>
#include <stdlib.h>
#include <time.h>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QVector>

namespace Ui {
class Prolong;
}

class Prolong : public QDialog
{
    Q_OBJECT
     //количество нейронов входного слоя
const int first_layer_neurons = 10;
public:
    explicit Prolong(QWidget *parent = 0);
    ~Prolong();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Prolong *ui;
    QSqlTableModel *model;
    std::vector<int> sellingsAmount;
    std::vector<std::vector<double> > Wij;
    std::vector<double> Wjk;
    std::vector<double> Tj;
    std::vector<double> Yj;
    std::vector<double> gamma1;

    QVector<double> steps;
    QVector<double> sellings;
    double Tk;
    void EducateNet();
    void PredictSellings();
};

#endif // PROLONG_H
