/********************************************************************************
** Form generated from reading UI file 'connectiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONDIALOG_H
#define UI_CONNECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConnectionDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *login;
    QLabel *label_2;
    QLineEdit *pwd;
    QLabel *label_3;
    QLineEdit *host;
    QLabel *label_4;
    QLineEdit *database;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *ConnectionDialog)
    {
        if (ConnectionDialog->objectName().isEmpty())
            ConnectionDialog->setObjectName(QStringLiteral("ConnectionDialog"));
        ConnectionDialog->resize(422, 170);
        QFont font;
        font.setPointSize(10);
        ConnectionDialog->setFont(font);
        verticalLayout = new QVBoxLayout(ConnectionDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(ConnectionDialog);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        login = new QLineEdit(ConnectionDialog);
        login->setObjectName(QStringLiteral("login"));

        formLayout->setWidget(0, QFormLayout::FieldRole, login);

        label_2 = new QLabel(ConnectionDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        pwd = new QLineEdit(ConnectionDialog);
        pwd->setObjectName(QStringLiteral("pwd"));
        pwd->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, pwd);

        label_3 = new QLabel(ConnectionDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        host = new QLineEdit(ConnectionDialog);
        host->setObjectName(QStringLiteral("host"));

        formLayout->setWidget(2, QFormLayout::FieldRole, host);

        label_4 = new QLabel(ConnectionDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        database = new QLineEdit(ConnectionDialog);
        database->setObjectName(QStringLiteral("database"));

        formLayout->setWidget(3, QFormLayout::FieldRole, database);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(ConnectionDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ConnectionDialog);

        QMetaObject::connectSlotsByName(ConnectionDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectionDialog)
    {
        ConnectionDialog->setWindowTitle(QApplication::translate("ConnectionDialog", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265 \320\272 \320\261\320\260\320\267\320\265 \320\264\320\260\320\275\320\275\321\213\321\205", Q_NULLPTR));
        label->setText(QApplication::translate("ConnectionDialog", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217:", Q_NULLPTR));
        login->setText(QApplication::translate("ConnectionDialog", "postgres", Q_NULLPTR));
        label_2->setText(QApplication::translate("ConnectionDialog", "\320\237\320\260\321\200\320\276\320\273\321\214:", Q_NULLPTR));
        pwd->setText(QApplication::translate("ConnectionDialog", "postgrespass", Q_NULLPTR));
        label_3->setText(QApplication::translate("ConnectionDialog", "\320\245\320\276\321\201\321\202:", Q_NULLPTR));
        host->setText(QApplication::translate("ConnectionDialog", "localhost", Q_NULLPTR));
        label_4->setText(QApplication::translate("ConnectionDialog", "\320\221\320\260\320\267\320\260 \320\264\320\260\320\275\320\275\321\213\321\205:", Q_NULLPTR));
        database->setText(QApplication::translate("ConnectionDialog", "ComputerShop", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ConnectionDialog", "OK", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConnectionDialog: public Ui_ConnectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONDIALOG_H
