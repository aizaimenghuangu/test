/********************************************************************************
** Form generated from reading UI file 'timeselect.ui'
**
** Created: Wed Apr 10 17:40:13 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMESELECT_H
#define UI_TIMESELECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimeSelect
{
public:
    QGroupBox *groupBox;
    QDateTimeEdit *fromDateTimeEdit;
    QGroupBox *groupBox_2;
    QDateTimeEdit *endDateTimeEdit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *TimeSelect)
    {
        if (TimeSelect->objectName().isEmpty())
            TimeSelect->setObjectName(QString::fromUtf8("TimeSelect"));
        TimeSelect->resize(233, 236);
        groupBox = new QGroupBox(TimeSelect);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 211, 80));
        fromDateTimeEdit = new QDateTimeEdit(groupBox);
        fromDateTimeEdit->setObjectName(QString::fromUtf8("fromDateTimeEdit"));
        fromDateTimeEdit->setGeometry(QRect(10, 30, 194, 22));
        groupBox_2 = new QGroupBox(TimeSelect);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 110, 211, 80));
        endDateTimeEdit = new QDateTimeEdit(groupBox_2);
        endDateTimeEdit->setObjectName(QString::fromUtf8("endDateTimeEdit"));
        endDateTimeEdit->setGeometry(QRect(10, 30, 194, 22));
        widget = new QWidget(TimeSelect);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(60, 200, 158, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        okBtn = new QPushButton(widget);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cancelBtn = new QPushButton(widget);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);


        retranslateUi(TimeSelect);

        QMetaObject::connectSlotsByName(TimeSelect);
    } // setupUi

    void retranslateUi(QDialog *TimeSelect)
    {
        TimeSelect->setWindowTitle(QApplication::translate("TimeSelect", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TimeSelect", "\350\265\267\345\247\213\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        fromDateTimeEdit->setDisplayFormat(QApplication::translate("TimeSelect", "yyyy-MM-dd H:mm:ss", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("TimeSelect", "\346\210\252\346\255\242\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        endDateTimeEdit->setDisplayFormat(QApplication::translate("TimeSelect", "yyyy-MM-dd H:mm:ss", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("TimeSelect", "\347\241\256\345\256\232(&O)", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("TimeSelect", "\345\217\226\346\266\210(&C)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TimeSelect: public Ui_TimeSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMESELECT_H
