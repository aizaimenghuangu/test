#ifndef CListenThread_H
#define CListenThread_H

#include <QThread>
#include <QtNetwork/QUdpSocket>

const quint16 LISTEN_PORT = 6667;
const quint16 SEND_PORT = 6668;

class QUdpSocket;
class CListenThread : public QThread
{
    Q_OBJECT
public:
    explicit CListenThread(QObject *parent = 0);
    
signals:
    
public slots:
protected:
    void run();

private:
    bool listen();
    void analyzing(QString &sMessage);

    QUdpSocket *p_ListenUdpSoket;
    QHostAddress m_ServerIP;
    QHostAddress m_LocalIP;

    enum
    {
        USER, // 行程拥有者
        PID, // pid
        CPU, // 占用的 CPU 使用率
        MEM, // 占用的记忆体使用率
        VSZ, // 占用的虚拟记忆体大小
        RSS, // 占用的记忆体大小
        TTY, // 终端的次要装置号码 (minor device number of tty)
        STAT, // 该行程的状态, //
//        D, // 不可中断的静止
//        R, // 正在执行中
//        S, // 静止状态
//        T, // 暂停执行
//        Z, // 不存在但暂时无法消除
//        W, // 没有足够的记忆体分页可分配
//        <, // 高优先序的行程
//        N, // 低优先序的行程
//        L, // 有记忆体分页分配并锁在记忆体内 (即时系统或捱A I/O)
        START, // 行程开始时间
        TIME, // 执行的时间
        COMMAND //所执行的指令
    };

private slots:
    void processPendingDatagrams();
    void getIPFromMainThread(QString sLocalIP, QString sServerIP);
signals:
    void updateData(QString sServerType, QString sUser, int iPid, double cpu, double mem);
};


class QThreadImpl : public QThread
{
public:
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};

#endif // CListenThread_H
