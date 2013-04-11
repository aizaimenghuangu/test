#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QVariant>


class HistoryData
{
public:
    QString sRemoteIP;
    QString sServerName;
    QString sDateTime;
    double dMemory;
    double dCPU;
};

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = 0);

public:
    bool openDB();
    bool deleteDB();
    bool createTable();
    int insertData(QString remoteIP, QString serverName, QString time, double memory, double dCpu);
    bool getData(QString sServerType, QString sFromTime, QString sEndTime, HistoryData*& HistoryInfo);
    bool getData(QString sServerType, QString sFromTime, QString sEndTime, QVector<QPointF> &CPU_data, QVector<QPointF> &MEM_data);
    bool deleteData(int id);

    QSqlError lastError();

private:
    QSqlDatabase db;

signals:

public slots:

};

#endif // DATABASEMANAGER_H
