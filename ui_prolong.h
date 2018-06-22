/********************************************************************************
** Form generated from reading UI file 'prolong.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROLONG_H
#define UI_PROLONG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Prolong
{
public:
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *eps;
    QLabel *proc;
    QCustomPlot *netPlot;

    void setupUi(QDialog *Prolong)
    {
        if (Prolong->objectName().isEmpty())
            Prolong->setObjectName(QStringLiteral("Prolong"));
        Prolong->resize(486, 464);
        QFont font;
        font.setPointSize(10);
        Prolong->setFont(font);
        verticalLayout = new QVBoxLayout(Prolong);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tableView = new QTableView(Prolong);
        tableView->setObjectName(QStringLiteral("tableView"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(tableView);

        pushButton = new QPushButton(Prolong);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Prolong);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        eps = new QLabel(Prolong);
        eps->setObjectName(QStringLiteral("eps"));

        horizontalLayout->addWidget(eps);

        proc = new QLabel(Prolong);
        proc->setObjectName(QStringLiteral("proc"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        proc->setFont(font1);

        horizontalLayout->addWidget(proc);


        verticalLayout->addLayout(horizontalLayout);

        netPlot = new QCustomPlot(Prolong);
        netPlot->setObjectName(QStringLiteral("netPlot"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(netPlot->sizePolicy().hasHeightForWidth());
        netPlot->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(netPlot);


        retranslateUi(Prolong);

        QMetaObject::connectSlotsByName(Prolong);
    } // setupUi

    void retranslateUi(QDialog *Prolong)
    {
        Prolong->setWindowTitle(QApplication::translate("Prolong", "Dialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Prolong", "\320\237\321\200\320\276\320\263\320\275\320\276\320\267\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\277\321\200\320\276\320\264\320\260\320\266", Q_NULLPTR));
        label->setText(QApplication::translate("Prolong", "\320\241\321\203\320\274\320\274\320\260\321\200\320\275\320\260\321\217 \321\201\321\200\320\265\320\264\320\275\320\265\320\272\320\262\320\260\320\264\321\200\320\260\321\202\320\270\321\207\320\275\320\260\321\217 \320\276\321\210\320\270\320\261\320\272\320\260 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217:", Q_NULLPTR));
        eps->setText(QApplication::translate("Prolong", "-", Q_NULLPTR));
        proc->setText(QApplication::translate("Prolong", "-", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Prolong: public Ui_Prolong {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROLONG_H
