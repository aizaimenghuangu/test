#include "listenthread.h"


#include <QtNetwork/QHostInfo>
#include <QtNetwork/QNetworkInterface>
#include <QStringList>

CListenThread::CListenThread(QObject *parent) :
    QThread(parent)
{
    m_ServerIP = QHostAddress::Null;
    m_LocalIP = QHostAddress::Null;
}

void CListenThread::run()
{

    //初始化套接字，QThread中只有在run()中建立的对象才是真正的属于子线程
    //所以在此初始化p_ListenUdpSoket
    p_ListenUdpSoket = new QUdpSocket();

    if(!listen())
    {
        qDebug() << __FILE__ <<":"<< __LINE__ << "ERROR:端口:" + QString::number(LISTEN_PORT) + "被占用, 将无法收到对应的日志信息";
    }

    //
    QString message = "test";
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out << message;

    p_ListenUdpSoket->writeDatagram(datagram, m_ServerIP, SEND_PORT);

    this->exec();
}

/***********************************************************************
 * 函数名称： listen
 * 函数功能： 监听事件
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月14日21:00:52
 ***********************************************************************/
bool CListenThread::listen()
{
    if(!p_ListenUdpSoket->bind(LISTEN_PORT))
    {
        qDebug() << __FILE__ <<":"<< __LINE__ <<"   p_ListenUdpSoket->bind fail!";
        return false;
    }
    connect(p_ListenUdpSoket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()), Qt::DirectConnection);
    return true;
}

/***********************************************************************
 * 函数名称： processPendingDatagrams
 * 函数功能： 数据处理
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月14日21:00:52
 ***********************************************************************/
void CListenThread::processPendingDatagrams()
{
    static QByteArray datagram;
    datagram.resize(p_ListenUdpSoket->pendingDatagramSize());
    p_ListenUdpSoket->readDatagram(datagram.data(), datagram.size());

    static QString message;
    QDataStream in(&datagram, QIODevice::ReadOnly);
    in >> message;

    if(!message.compare("HeartBeat"))
    {
        //回复心跳包消息
        QString message = "HeartBeat";
        QByteArray datagram;
        QDataStream out(&datagram, QIODevice::WriteOnly);
        out << message;

        p_ListenUdpSoket->writeDatagram(datagram, m_ServerIP, SEND_PORT);
    }
    else
    {
        //处理消息
        analyzing(message);
    }
}

/***********************************************************************
 * 函数名称： analyzing
 * 函数功能： 数据解析
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月14日21:00:52
 ***********************************************************************/
void CListenThread::analyzing(QString &sMessage)
{
    QStringList sServerInfo = sMessage.split("\n");
    for(int i = 0; i < sServerInfo.size(); i++)
    {
        QStringList sInfoList = sServerInfo[i].split(" ", QString::SkipEmptyParts);
        if(sServerInfo[i].contains("fileservice"))
        {
            QLocale::setDefault(QLocale::German);
            emit updateData("fileservice", sInfoList[USER], sInfoList[PID].toInt(),
                            sInfoList[CPU].toDouble(), sInfoList[MEM].toDouble());
        }
        else if(sServerInfo[i].contains("tsserver"))
        {
            QLocale::setDefault(QLocale::German);
            emit updateData("tsserver", sInfoList[USER], sInfoList[PID].toInt(),
                            sInfoList[CPU].toDouble(), sInfoList[MEM].toDouble());
        }
        else if(sServerInfo[i].contains("vodserver"))
        {
            QLocale::setDefault(QLocale::German);
            emit updateData("vodserver", sInfoList[USER], sInfoList[PID].toInt(),
                            sInfoList[CPU].toDouble(), sInfoList[MEM].toDouble());
        }
        else if(sServerInfo[i].contains("smftp"))
        {
            QLocale::setDefault(QLocale::German);
            emit updateData("smftp", sInfoList[USER], sInfoList[PID].toInt(),
                            sInfoList[CPU].toDouble(), sInfoList[MEM].toDouble());
        }
        else if(sServerInfo[i].contains("stblogservice"))
        {
            QLocale::setDefault(QLocale::German);
            emit updateData("stblogservice", sInfoList[USER], sInfoList[PID].toInt(),
                            sInfoList[CPU].toDouble(), sInfoList[MEM].toDouble());
        }
        else if(sServerInfo[i].contains("updateservice"))
        {
            QLocale::setDefault(QLocale::German);
            emit updateData("updateservice", sInfoList[USER], sInfoList[PID].toInt(),
                            sInfoList[CPU].toDouble(), sInfoList[MEM].toDouble());
        }
    }
}


/***********************************************************************
 * 函数名称： getIPFromMainThread
 * 函数功能： 从主线程获取本机IP地址和远程IP地址
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月14日21:00:52
 ***********************************************************************/
void CListenThread::getIPFromMainThread(QString sLocalIP, QString sServerIP)
{
    m_LocalIP = QHostAddress(sLocalIP);
    m_ServerIP = QHostAddress(sServerIP);
}
