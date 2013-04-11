#include "databasemanager.h"
#include <QDebug>
#include <QPointF>

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
}

bool DatabaseManager::openDB()
{
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");

#ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("my.db.sqlite");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
#else
    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    db.setDatabaseName("HistoryData.db");
#endif

    // Open databasee
    return db.open();
}

QSqlError DatabaseManager::lastError()
{
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

bool DatabaseManager::deleteDB()
{
    // Close database
    db.close();

#ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("my.db.sqlite");
    path = QDir::toNativeSeparators(path);
    return QFile::remove(path);
#else

    // Remove created database binary file
    return QFile::remove("HistoryData.db");
#endif
}

bool DatabaseManager::createTable()
{
    // Create table "HIS_INFO"
    bool ret = false;
    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec("create table IF NOT EXISTS HIS_INFO(remoteip varchar, servername varchar, datetime varchar, memory varchar, cpu varchar)");    //新建HistoryInfo表

    }
    return ret;
}

int DatabaseManager::insertData(QString sRemoteIP, QString sServerName, QString sDateTime, double dMemory, double dCpu)
{
    int newId = -1;
    bool ret = false;

    if (db.isOpen())
    {
        //http://www.sqlite.org/autoinc.html
        // NULL = is the keyword for the autoincrement to generate next value

        QSqlQuery query;
        QString sSql = QString("insert into HIS_INFO values('%1','%2','%3',%4,%5)")
                .arg(sRemoteIP).arg(sServerName).arg(sDateTime).arg(dMemory).arg(dCpu);
        ret = query.exec(sSql);

        // Get database given autoincrement value
        if (ret)
        {
            // http://www.sqlite.org/c3ref/last_insert_rowid.html
            newId = query.lastInsertId().toInt();
        }

    }
    return newId;
}
bool DatabaseManager::getData(QString sServerType, QString sFromTime, QString sEndTime, HistoryData*& HIS_INFO)
{
    bool ret = false;

    QString sSql = QString("select * from HIS_INFO where servername = %1 and  datetime >= %2 and datetime<= %2").arg(sServerType).arg(sFromTime).arg(sEndTime);

    QSqlQuery query(sSql);
    if (query.next())
    {
        HIS_INFO->sRemoteIP = query.value(0).toString();
        HIS_INFO->sServerName = query.value(1).toString();
        HIS_INFO->sDateTime = query.value(2).toString();
        HIS_INFO->dMemory = query.value(3).toDouble();
        HIS_INFO->dCPU = query.value(4).toDouble();
        ret = true;
    }

    return ret;
}

bool DatabaseManager::getData(QString sServerType, QString sFromTime, QString sEndTime, QVector<QPointF> &CPU_data, QVector<QPointF> &MEM_data)
{
    bool ret = false;


    QString sSql = QString("select * from HIS_INFO where servername='%1' and datetime(datetime)>datetime('%2') and  datetime(datetime)<datetime('%3')").arg(sServerType).arg(sFromTime).arg(sEndTime);

    QSqlQuery query(sSql);
    int i = -1;
    while (query.next())
    {
        i++;
        CPU_data.append(QPointF(i, query.value(3).toDouble()));
        MEM_data.append(QPointF(i, query.value(4).toDouble()));

        //        ret = true;
    }
    ret = true;
    return ret;
}

bool DatabaseManager::deleteData(int id)
{
    bool ret = false;
    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(QString("delete from HIS_INFO where id=%1").arg(id));
    }
    return ret;
}
