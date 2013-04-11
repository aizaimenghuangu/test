/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created: Wed Apr 10 17:40:13 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *serverIPLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *LocalIPLineEdit;
    QPlainTextEdit *errorLog;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QDialogButtonBox *buttonBox;
    QPushButton *linkTestBtn;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(290, 216);
        layoutWidget = new QWidget(login);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 40, 241, 168));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        serverIPLineEdit = new QLineEdit(layoutWidget);
        serverIPLineEdit->setObjectName(QString::fromUtf8("serverIPLineEdit"));

        horizontalLayout->addWidget(serverIPLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        LocalIPLineEdit = new QLineEdit(layoutWidget);
        LocalIPLineEdit->setObjectName(QString::fromUtf8("LocalIPLineEdit"));

        horizontalLayout_2->addWidget(LocalIPLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        errorLog = new QPlainTextEdit(layoutWidget);
        errorLog->setObjectName(QString::fromUtf8("errorLog"));

        verticalLayout_2->addWidget(errorLog);

        verticalSpacer = new QSpacerItem(20, 58, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_3->addWidget(buttonBox);

        linkTestBtn = new QPushButton(layoutWidget);
        linkTestBtn->setObjectName(QString::fromUtf8("linkTestBtn"));

        horizontalLayout_3->addWidget(linkTestBtn);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(login);
        QObject::connect(buttonBox, SIGNAL(accepted()), login, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), login, SLOT(reject()));

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QApplication::translate("login", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("login", "\350\277\234\347\250\213\346\234\215\345\212\241\345\231\250IP\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("login", "\346\234\254\346\234\272 IP \345\234\260\345\235\200\357\274\232", 0, QApplication::UnicodeUTF8));
        linkTestBtn->setText(QApplication::translate("login", "\350\277\236\346\216\245\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
