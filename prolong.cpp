#include "prolong.h"
#include "ui_prolong.h"

Prolong::Prolong(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prolong)
{
    ui->setupUi(this);
    this->showMaximized();
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

Prolong::~Prolong()
{
    delete ui;
}

void Prolong::EducateNet() //ошибка обучения
{
    double E1 = 0;
    double S, E, gamma, Y;
    //количество нейронов скрытого слоя
    int hidden = 7;


    //размер обучающей выборки
    int sample_size = this->sellingsAmount.size();

    //скорость обучения
    double alpha = 0.095;


    // итерация обучения
    int education_step = 0;
    //весовые коэффициенты скрытого слоя

    Wij.resize(first_layer_neurons);
    for(unsigned int i = 0; i < Wij.size(); ++i)
        Wij[i].resize(hidden);
    //весы выходного слоя
    Wjk.resize(hidden);
    //пороги скрытого слоя
    Tj.resize(hidden);
    Yj.resize(hidden);
    gamma1.resize(hidden);
    /*т.к. данные о продажах не имеют никакой математической зависимости под собой,
     * можно принять допустимую ошибку обучения.
     * допустимая ошибка: примем приемлимое расхождение выходного значения и
эталона = 0,5; тогда среднеквадратичная ошибка равна (0,5*0,5)/2, умножим
на количество получаемых выходных значений. Например, обучающая выборка
состоит из 10 значений, тогда допустимая ошибка обучения будет равна:
10-(количество входов сети)*0,25*0,5 = (например) 5*0,25*0,5 = 0,625*/

    double okGamma = 0.7;
    double okError = (sample_size - this->first_layer_neurons)*pow(okGamma,2)*0.5;

    int net_step = 0;

    //========начальная инициализация весов и пороговых значений
    srand(time(NULL));
    //диапазон -0,05;0,05
    for (unsigned int i = 0; i < Wij.size(); ++i)
        for(unsigned int j = 0; j < Wij[i].size(); ++j)
            Wij[i][j] = (double) rand() / RAND_MAX  * 0.1 -0.05;
    for(unsigned int i=0; i < Wjk.size(); ++i) {
        Wjk[i] = (double) rand() / RAND_MAX  * 0.1 -0.05;
        Tj[i] = (double) rand() / RAND_MAX  * 0.1 -0.05;
    }
    Tk = (double) rand() / RAND_MAX  * 0.1 -0.05;
    //=================================
    QVector<double> Yjj;
    QVector<double> steps_;
    do {
        E1 = E;
        E = 0;
        net_step = 0;
        Yjj.clear();
        steps_.clear();



        do {
            //=========выходные значения для скрытого слоя
            //сигмоидная функция обучения
            for(int j = 0; j < hidden; ++j) {
                S = 0;
                for (int i = 0; i < first_layer_neurons; i++)
                    S += Wij[i][j] * sellingsAmount[net_step + i];
                S -= Tj[j];
                Yj[j] = 1 / (1 + exp(-S));
            }
            //=========выходное значение
            Y = 0;
            for(int j = 0; j < hidden; ++j) {
                Y += Wjk[j]*Yj[j];
            }
            Y -= Tk;

            //==========находим ошибку гамма
            //для выходного слоя
            gamma = Y - sellingsAmount[first_layer_neurons + net_step];
            //для скрытого слоя
            for(int j = 0; j < hidden; ++j)
                gamma1[j] = gamma*Yj[j]*(1-Yj[j])*Wjk[j];
            //======модификация весовых коэффициентов и пороговых значений
            //===для выходного слоя
            for(int j = 0; j < hidden; ++j)
                Wjk[j] -= alpha*gamma*Yj[j];
            Tk += alpha*gamma;
            //========для скрытого слоя
            for(int i = 0; i < first_layer_neurons; ++i)
                for(int j = 0; j < hidden; ++j)
                    Wij[i][j] -= alpha*gamma1[j]*Yj[j]*(1-Yj[j])*sellingsAmount[net_step + i];
            for(int j = 0; j < hidden; ++j)
                Tj[j] += alpha*gamma1[j]*Yj[j]*(1-Yj[j]);

            E += pow(Y - sellingsAmount[first_layer_neurons + net_step], 2)*0.5;
            //Запишем в файл процесс обучения сети
            steps_.push_back(net_step+1);
            Yjj.push_back(Y);

            QFile result_file(QCoreApplication::applicationDirPath()+"/neteducation.txt");
            if (!result_file.open(QIODevice::Append))
                return;

            QTextStream out(&result_file);
            out << net_step+1 << "\t" <<
                   sellingsAmount[net_step] << "\t" <<
                   Y << endl;
            result_file.close();
            net_step++;
        }
        while (net_step + first_layer_neurons < sample_size);

        education_step++;
        QFile result_file(QCoreApplication::applicationDirPath()+"/neteducation.txt");
        if (!result_file.open(QIODevice::Append))
            return;

        QTextStream out(&result_file);
        out << E << endl;
        result_file.close();
        QApplication::processEvents();
        ui->eps->setText(QString::number(E));



    } while (E >= okError);//(abs(E1-E) >= eps);


    //прогнозирование

    int prolong = 10, p = 0; //на prolong недель вперед
    ui->proc->setText("Прогнозирование на "+QString::number(prolong)+ "недель вперед...");
    do {
        for(int j = 0; j < hidden; ++j) {
            S = 0;
            for (int i = 0; i < first_layer_neurons; i++)
                S += Wij[i][j] * Yjj[Yjj.size()-first_layer_neurons+i];
            S -= Tj[j];
            Yj[j] = 1 / (1 + exp(-S));
        }
        //=========выходное значение
        Y = 0;
        for(int j = 0; j < hidden; ++j) {
            Y += Wjk[j]*Yj[j];
        }
        Y -= Tk;
                qDebug() << Y << steps_.size();
        Yjj.push_back(Y);
        steps_.push_back(steps_.size()+1);
        ++p;
    }while (p < prolong);

    ui->netPlot->addGraph();
    ui->netPlot->graph(1)->setPen(QPen(Qt::green));
    ui->netPlot->graph(1)->setData(steps_, Yjj);
    ui->netPlot->rescaleAxes();
    ui->netPlot->replot();


}

void Prolong::on_pushButton_clicked()
{
    ui->proc->setText("Нейронная сеть обучается...");
    int categoryId = model->data(model->index(ui->tableView->currentIndex().row(),0)).toInt();
    QSqlQuery query;
    //найдем, с какой даты начались продажи
    query.prepare("select date_::date from sellings, goods "
                  "where sellings.goods_id = goods.id and "
                  "goods.category_id = :id order by date_ limit 1");
    query.bindValue(":id", QVariant(categoryId));
    query.exec();
    query.next();
    qDebug() << query.value(0).toString();
    if (query.value(0).toString() != "") {
        QDate date1 = query.value(0).toDate();
        //в разрезе недель
        QDate date2 = date1.addDays(7);;
        sellingsAmount.clear();
        sellingsAmount.resize(0);
        sellings.clear();
        steps.clear();
        ui->netPlot->clearGraphs();
        ui->netPlot->rescaleAxes();
        int i = 0;
        while (date2 < QDate::currentDate()) {
            ++i;

            query.clear();
            query.prepare("select sum(sellings.amount) from sellings, goods "
                          "where sellings.goods_id = goods.id and "
                          "sellings.date_ BETWEEN :date1 AND :date2 and "
                          "goods.category_id = :catId");
            query.bindValue(":date1", QVariant(date1));
            query.bindValue(":date2", QVariant(date2));
            query.bindValue(":catId", QVariant(categoryId));
            query.exec();
            query.next();
            qDebug() << query.value(0).toInt();
            this->sellingsAmount.push_back(query.value(0).toInt());
            if (i >= first_layer_neurons+1
                    ) {
                sellings.push_back(query.value(0).toInt());
                steps.push_back(i-first_layer_neurons);
            }

            date1 = date2;
            date2 = date1.addDays(7);
        }
        if (sellingsAmount.size() < 2*first_layer_neurons) {
            QMessageBox::information(this, tr("Ошибка"),
                                     tr("Выборка данных слишком мала для прогнозирования!\n"
                                        "Необходимо собрать данных минимум с 10 недель (~2.5 месяца)!"));
            return;
        }
        else {
            //задаем допустимую ошибку

            ui->netPlot->clearGraphs();
            ui->netPlot->addGraph();
            ui->netPlot->graph(0)->setPen(QPen(Qt::red));
            ui->netPlot->graph(0)->setData(steps, sellings);
            ui->netPlot->rescaleAxes();
            ui->netPlot->replot();

            EducateNet();
        }
    }
    else
        QMessageBox::information(this, tr("Ошибка"),
                                 tr("Продаж по этой категории не обнаружено!"));
}
