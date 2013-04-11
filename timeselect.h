#ifndef TIMESELECT_H
#define TIMESELECT_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class TimeSelect;
}

class TimeSelect : public QDialog
{
    Q_OBJECT

public:
    explicit TimeSelect(QWidget *parent = 0);
    ~TimeSelect();

private:
    Ui::TimeSelect *ui;
    QString sFromTime;
    QString sEndTime;

private slots:
    void getSettingTime();
signals:
    void sendTimeToMain(QString, QString);


};

#endif // TIMESELECT_H
