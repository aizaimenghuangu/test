#include "insertthread.h"
#include <QDebug>

InsertThread::InsertThread(QObject *parent) :
    QThread(parent)
{
    initDB();
}

void InsertThread::run()
{
    m_pThreadDB->insertData(m_sRemoteIP, m_sServerType, m_sDateTime, m_MEM, m_CPU);
}

void InsertThread::initDB()
{
    m_pThreadDB = new DatabaseManager();
}

void InsertThread::getInsertData(DatabaseManager *db, QString sRemoteIP, QString sServerType, QString sDateTime, double mem, double cpu)
{
    m_sRemoteIP = sRemoteIP;
    m_sServerType = sServerType;
    m_sDateTime = sDateTime;
    m_MEM = mem;
    m_CPU = cpu;
    m_pThreadDB = db;
}
