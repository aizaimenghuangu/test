#ifndef INSERTTHREAD_H
#define INSERTTHREAD_H

#include <QThread>
#include "databasemanager.h"

class DatabaseManager;
class InsertThread : public QThread
{
    Q_OBJECT
public:
    explicit InsertThread(QObject *parent = 0);
private:
    void initDB();

    DatabaseManager *m_pThreadDB;

    QString m_sRemoteIP;
    QString m_sServerType;
    QString m_sDateTime;
    double m_MEM;
    double m_CPU;

signals:

public slots:
    void getInsertData(DatabaseManager *db, QString sRemoteIP, QString sServerType, QString sDateTime, double mem, double cpu);

protected:
    void run();


};

#endif // INSERTTHREAD_H
