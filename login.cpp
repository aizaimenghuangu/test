#include "login.h"
#include "ui_login.h"

#include <QtNetwork/QHostInfo>
#include <QAbstractButton>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#include <QProcess>
#include <QDebug>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    initData();
    this->setWindowTitle("登陆配置");
}

login::~login()
{
    delete ui;
}

/***********************************************************************
 * 函数名称： initData
 * 函数功能： 初始化相关数据
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月25日10:37:05
 ***********************************************************************/
void login::initData()
{
    m_bLinkOk = false;

    //配置IP地址输入的合法性
    setIP4Validator(ui->serverIPLineEdit);
    setIP4Validator(ui->LocalIPLineEdit);

    ui->serverIPLineEdit->setPlaceholderText("远程服务器IP地址");
    ui->LocalIPLineEdit->setToolTip("如果获取本机IP地址有误，请重新填写");

    //获取本机IP地址
    QString sLocalIPAdd = getLocalIPAddress().toString();
    ui->LocalIPLineEdit->setText(sLocalIPAdd);
    ui->serverIPLineEdit->setText("127.0.0.1");

    //测试定时器
    m_pTestLinkTimer = new QTimer(this);
    m_pTestLinkTimer->setInterval(TEST_TIMEOUT);
    connect(m_pTestLinkTimer,SIGNAL(timeout()),this,SLOT(testLinkTimerOut()));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);//默认不可用，可以测试通过才能使用
    ui->buttonBox->button(QDialogButtonBox::Ok)->setToolTip("请先进行【连接测试】");
    ui->errorLog->hide();
    ui->errorLog->setReadOnly(true);
}


/***********************************************************************
 * 函数名称： getLocalIPAddress
 * 函数功能： 获取本机IP地址
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月25日10:37:05
 ***********************************************************************/
QHostAddress login::getLocalIPAddress()
{
    QString vAddress;

#ifdef _WIN32
    QHostInfo vHostInfo = QHostInfo::fromName(QHostInfo::localHostName());
    QList<QHostAddress> vAddressList = vHostInfo.addresses();
#else
    QList<QHostAddress> vAddressList = QNetworkInterface::allAddresses();
#endif
    for(int i = 0; i < vAddressList.size(); i++)
    {
        if(!vAddressList.at(i).isNull() &&
                vAddressList.at(i) != QHostAddress::LocalHost &&
                vAddressList.at(i).protocol() ==  QAbstractSocket::IPv4Protocol)
        {
            vAddress = vAddressList.at(i).toString();
            break;
        }
    }

    return QHostAddress(vAddress);
}

/***********************************************************************
 * 函数名称： setIP4Validator
 * 函数功能： 输入时检查IP地址的合法性，如果是非法的IP地址则无法进行输入
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月25日10:37:05
 ***********************************************************************/
void login::setIP4Validator(QLineEdit *lineEdit)
{
    QString Octet = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    lineEdit->setValidator(new QRegExpValidator(
                               QRegExp("^" + Octet + "\\." + Octet + "\\." + Octet + "\\." + Octet + "$"), this));
}


void login::on_buttonBox_clicked(QAbstractButton *button)
{
    if("确定" == button->text())
    {
        QString sLocalIP = getLocalIPAddress().toString();
        QString sRemoteIP = ui->serverIPLineEdit->text();

        emit sendIPToMain(sLocalIP, sRemoteIP);//向主程序发送一个信息号，告知本机IP地址和远程IP地址(使用全局变量也许是一个更好的办法)
    }
    else
    {
        emit cancelBtnClick();
    }
}

/***********************************************************************
 * 函数名称： on_linkTestBtn_clicked
 * 函数功能： 连接测试
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月25日10:37:05
 ***********************************************************************/
void login::on_linkTestBtn_clicked()
{
    ui->linkTestBtn->setEnabled(false);
    m_pTestLinkSocket = new QUdpSocket();

    if(!listen())
    {
        qDebug() << "ERROR:端口:" + QString::number(LOGIN_LISTEN_PORT + 1) + "被占用, 将无法收到对应的日志信息";
    }

    QString message = "TestLink";
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out << message;


    m_pTestLinkSocket->writeDatagram(datagram, QHostAddress(ui->serverIPLineEdit->text()), LOGIN_SEND_PORT);

    //启动超时定时器
    m_pTestLinkTimer->start();
}


/***********************************************************************
 * 函数名称： listen
 * 函数功能： 监听事件
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月14日21:00:52
 ***********************************************************************/
bool login::listen()
{
    if(!m_pTestLinkSocket->bind(LOGIN_LISTEN_PORT))
    {
        qDebug() << __FILE__ <<":"<< __LINE__ <<"   p_ListenUdpSoket->bind fail!";
        return false;
    }
    connect(m_pTestLinkSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()), Qt::DirectConnection);
    return true;
}

/***********************************************************************
 * 函数名称： PingAClient
 * 函数功能： ping 客户端，查看是否可以ping通
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月14日21:00:52
 ***********************************************************************/
bool login::PingAClient(QString clientip)
{
    if (clientip.isEmpty())
        return false;

    int iTimeOut=2000;
    QDateTime dd=QDateTime::currentDateTime().addMSecs(iTimeOut);
#ifdef WIN32
    QString sCommand=QString("ping -n 1 -i 2 %1 ").arg(clientip);
#else
    QString sCommand=QString("ping -c1 -W2 %1 ").arg(clientip);
#endif
    QProcess process;
    process.start(sCommand);
    if (!process.waitForStarted(iTimeOut))
    {
        qDebug() << process.errorString();
        process.close();
        return false;
    }

    if (QDateTime::currentDateTime()>=dd)
    {
        process.close();
        return false;
    }

    //2..
    if (!process.waitForReadyRead(iTimeOut))
    {
        process.close();
        return false;
    }

    if (QDateTime::currentDateTime()>=dd)
    {
        process.close();
        return false;
    }

    //3..
    QByteArray bb=process.readAll();
    process.close();

    //4.analyse;
    QStringList ts;
    SpilitStr(QString::fromLocal8Bit(bb),"\n",ts);

#ifdef WIN32
    QString tag1=QString("来自 %1").arg(clientip);
#else
    QString tag1=QString(" from %1").arg(clientip);
#endif
    bool suc=false;
    for (int i=ts.count()-1;i>=0;i--)
    {
        if (QString(ts.value(i)).indexOf(tag1)>0)
        {
            suc=true;
            break;
        }
    }

    return suc;
}

/************************************************************************
 * 函数名称： SpilitStr
 * 函数功能： 字符串分割；
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年4月7日23:01:47
 ************************************************************************/
void login::SpilitStr(QString sourcestr,QString SeperatorChar,QStringList &ResultTS)
{
    ResultTS.clear();
    if ((SeperatorChar.isEmpty())  || (sourcestr.isEmpty()))
        return;

    ResultTS=sourcestr.split(SeperatorChar);
}

/***********************************************************************
 * 函数名称： processPendingDatagrams
 * 函数功能： 数据处理
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月14日21:00:52
 ***********************************************************************/
void login::processPendingDatagrams()
{
    m_bLinkOk = true;
    m_pTestLinkTimer->stop();

    static QByteArray datagram;
    datagram.resize(m_pTestLinkSocket->pendingDatagramSize());
    m_pTestLinkSocket->readDatagram(datagram.data(), datagram.size());

    static QString message;
    QDataStream in(&datagram, QIODevice::ReadOnly);
    in >> message;

    if(!message.compare("TestLinkOK"))
    {
        ui->linkTestBtn->setEnabled(true);
        ui->errorLog->appendPlainText("连接" + ui->label->text() + ui->serverIPLineEdit->text()+ "成功");
        ui->errorLog->show();
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setToolTip("连接成功，请点击");
        m_pTestLinkSocket->close();
    }
}

/***********************************************************************
 * 函数名称： testLinkTimerOut
 * 函数功能： 测试连接定时器超时
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月14日21:00:52
 ***********************************************************************/
void login::testLinkTimerOut()
{
    qDebug() <<"timeout";
    if(!m_bLinkOk)
    {
        m_pTestLinkTimer->stop();

        //检查网络是否畅通
#if 0
        if(!PingAClient(ui->serverIPLineEdit->text()))
        {
            ui->errorLog->appendPlainText("无法ping通服务器,请确认网络连接;");
            ui->errorLog->show();
            qDebug() << "网络错误";
        }
        else
        {
            ui->errorLog->appendPlainText("可以ping通服务器\n可能是：\n①网络丢包，请重试；\n②服务器未开启。");
            qDebug() <<"服务端未开启";
        }
#endif
        ui->errorLog->appendPlainText("检测到【网络异常】,可能是：\n①网络丢包，请重试；\n②服务器未开启。\n");
        ui->errorLog->show();
    }
    m_bLinkOk = false;
    m_pTestLinkSocket->close();
    ui->linkTestBtn->setEnabled(true);
}
