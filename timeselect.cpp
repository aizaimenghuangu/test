#include "timeselect.h"
#include "ui_timeselect.h"
#include <QDebug>
#include <QMessageBox>

TimeSelect::TimeSelect(QWidget *parent) :
    QDialog(parent),
    sFromTime(""),
    sEndTime(""),
    ui(new Ui::TimeSelect)
{
    ui->setupUi(this);
    this->setWindowTitle("日期时间设置");
    ui->fromDateTimeEdit->setDisplayFormat("yyyy-MM-dd H:mm:ss");
    ui->fromDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->fromDateTimeEdit->setDateRange(QDate(2000, 1, 1), QDate(2069, 12, 31));

    ui->endDateTimeEdit->setDisplayFormat("yyyy-MM-dd H:mm:ss");
    ui->endDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->endDateTimeEdit->setDateRange(QDate(2000, 1, 1), QDate(2069, 12, 31));

    connect(ui->okBtn, SIGNAL(clicked()), this, SLOT(getSettingTime()));
    connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
}

TimeSelect::~TimeSelect()
{
    delete ui;
}

void TimeSelect::getSettingTime()
{
    sFromTime = ui->fromDateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
    sEndTime = ui->endDateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");

    if(ui->fromDateTimeEdit->date() > ui->endDateTimeEdit->date())
    {
        QMessageBox::warning(this, "提示1", "起始时间不能大于截止时间，请确认！", "确定(&O)");
        return ;
    }
    else
    {
        if(ui->fromDateTimeEdit->time() > ui->endDateTimeEdit->time())
        {
            QMessageBox::warning(this, "提示2", "起始时间不能大于截止时间，请确认！", "确定(&O)");
            return ;
        }
    }

    emit sendTimeToMain(sFromTime, sEndTime);
    this->close();
}
