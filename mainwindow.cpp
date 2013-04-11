#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mychart1.h"
#include "mygauge1.h"
#include "mygauge2.h"
#include "listenthread.h"
#include "login.h"
#include "databasemanager.h"
#include "timeselect.h"
#include "plotter.h"
#include "insertthread.h"

#include <QTimer>
#include <QPushButton>
#include <QMenu>
#include <QLabel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    m_sRemoteIP(""),
    m_sFromTime(""),
    m_sEndTime(""),
    ui(new Ui::MainWindow)
{
    //登陆窗口 设置远程IP地址和本机IP地址（默认获取，如果不匹配，可手动修改）
    m_pLogin = new login();
    connect(m_pLogin, SIGNAL(sendIPToMain(QString, QString)), this, SLOT(getIPFromLogin(QString, QString)));

    m_pLogin->show();
    if (m_pLogin->exec()==QDialog::Rejected)
    {
        QTimer::singleShot(0,this,SLOT(closeMainWin()));
        return;
    }

    //初始化界面
    initUI();

    //初始化数据库
    initDB();

    //初始化数据插入线程
    m_pInsertThread = new InsertThread();
    connect(this, SIGNAL(sendInsertData(DatabaseManager*, QString,QString,QString,double,double)),
            m_pInsertThread, SLOT(getInsertData(DatabaseManager*, QString,QString,QString,double,double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    //文件服务
    m_pFileSrvCpuView = new myChart1();
    m_pFileSrvMemView = new myChart1();

    //分发服务
    m_pTSCpuView = new myChart1();
    m_pTSMemView = new myChart1();

    //机顶盒启动服务
    m_pSMFTPCpuView = new myChart1();
    m_pSMFTPMemView = new myChart1();

    //视频服务
    m_pVODCpuView = new myChart1();
    m_pVODMemView = new myChart1();

    //升级服务
    m_pUPDATECpuView = new myChart1();
    m_pUPDATEMemView = new myChart1();

    //机顶盒日志服务
    m_pSTBLOGCpuView = new myChart1();
    m_pSTBLOGMemView = new myChart1();

    setGraphicVisible(false);
    //文件服务默认可见--默认显示
    m_pFileSrvCpuView->setVisible(true);
    m_pFileSrvMemView->setVisible(true);


    //类型选择按钮
    m_pTypeSelectBtn = new QPushButton("点击选择服务器");
    m_pTypeSelectBtn->setFixedWidth(110);

    m_pTypeSelectMenu = new QMenu();
    m_pTypeSelectMenu->addAction("文件服务", this, SLOT(fileserviceSelect()));
    m_pTypeSelectMenu->addAction("分发服务", this, SLOT(tsserverSelect()));
    m_pTypeSelectMenu->addAction("机顶盒启动服务", this, SLOT(smftpSelect()));
    m_pTypeSelectMenu->addAction("视频服务", this, SLOT(vodserverSelect()));
    m_pTypeSelectMenu->addAction("升级服务", this, SLOT(updateserviceSelect()));
    m_pTypeSelectMenu->addAction("机顶盒日志服务", this, SLOT(stblogserviceSelect()));
    m_pTypeSelectBtn->setMenu(m_pTypeSelectMenu);

    //历史记录信息查看
    m_pHistoryInfoBtn = new QPushButton("查看历史记录");
    m_pHistoryInfoBtn->setFixedWidth(110);
    m_pHistoryInfoMenu = new QMenu();
    m_pHistoryInfoMenu->addAction("文件服务", this, SLOT(fileserviceHistoryInfo()));
    m_pHistoryInfoMenu->addAction("分发服务", this, SLOT(tsserverHistoryInfo()));
    m_pHistoryInfoMenu->addAction("机顶盒启动服务", this, SLOT(smftpHistoryInfo()));
    m_pHistoryInfoMenu->addAction("视频服务", this, SLOT(vodserverHistoryInfo()));
    m_pHistoryInfoMenu->addAction("升级服务", this, SLOT(updateserviceHistoryInfo()));
    m_pHistoryInfoMenu->addAction("机顶盒日志服务", this, SLOT(stblogserviceHistoryInfo()));
    //xiongjinfei:以上内容是否可以用一个函数实现？
    m_pHistoryInfoBtn->setMenu(m_pHistoryInfoMenu);

    m_pAllMemView = new myGauge1(this);
    m_pAllMemViewLabel = new QLabel("\t\t\t总内存");

    m_pAllCpuView = new myGauge2(this);
    m_pAllCpuView->setAnimating(true);
    m_pAllCpuViewLabel = new QLabel("\t\t\t总CPU");

    QVBoxLayout *viewLayout = new QVBoxLayout();
    viewLayout->addWidget(m_pFileSrvCpuView);
    viewLayout->addWidget(m_pFileSrvMemView);

    viewLayout->addWidget(m_pTSCpuView);
    viewLayout->addWidget(m_pTSMemView);

    viewLayout->addWidget(m_pSMFTPCpuView);
    viewLayout->addWidget(m_pSMFTPMemView);

    viewLayout->addWidget(m_pVODCpuView);
    viewLayout->addWidget(m_pVODMemView);

    viewLayout->addWidget(m_pUPDATECpuView);
    viewLayout->addWidget(m_pUPDATEMemView);

    viewLayout->addWidget(m_pSTBLOGCpuView);
    viewLayout->addWidget(m_pSTBLOGMemView);
    viewLayout->setSpacing(0);

    QVBoxLayout *selectBtnLayout = new QVBoxLayout();
    selectBtnLayout->addWidget(m_pTypeSelectBtn);
    selectBtnLayout->addWidget(m_pHistoryInfoBtn);
    selectBtnLayout->addWidget(m_pAllMemView);
    selectBtnLayout->addWidget(m_pAllMemViewLabel);
    selectBtnLayout->addWidget(m_pAllCpuView);
    selectBtnLayout->addWidget(m_pAllCpuViewLabel);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addLayout(viewLayout);
    mainLayout->addLayout(selectBtnLayout);

    setLayout(mainLayout);
}

void MainWindow::initDB()
{
    m_pDB = new DatabaseManager();
    if(!m_pDB->openDB())
    {
        qDebug() << "数据库打开失败";
    }

    if(!m_pDB->createTable())
    {
        qDebug() << "创建table失败";
    }
}

void MainWindow::updateData(QString sServerType, QString sUser, int iPid, double cpu, double mem)
{
//        qDebug() <<sServerType;

    //将获取的数据写入数据库用于后期的查询(该操作会有些卡，可能后期需要放到线程中来实现)
    QString sDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    emit sendInsertData(m_pDB, m_sRemoteIP, sServerType, sDateTime, mem, cpu);
    m_pInsertThread->start();


    if(!sServerType.compare("fileservice"))
    {
        m_pFileSrvCpuView->setTitle(sServerType + "【PID:" + QString::number(iPid) + "】 CPU使用率 ");
        m_pFileSrvCpuView->addData(cpu);

        m_pFileSrvMemView->setTitle(sServerType + "【PID:" + QString::number(iPid) + "】 内存使用率 ");
        m_pFileSrvMemView->addData(mem);
    }
    else if(!sServerType.compare("smftp"))
    {
        m_pSMFTPCpuView->setTitle(sServerType + "【PID:" + QString::number(iPid) + "】 CPU使用率 ");
        m_pSMFTPCpuView->addData(cpu);

        m_pSMFTPMemView->setTitle(sServerType + "【PID:" + QString::number(iPid) + "】 内存使用率 ");
        m_pSMFTPMemView->addData(mem);
    }
    else if(!sServerType.compare("stblogservice"))
    {
        m_pSTBLOGCpuView->setTitle(sServerType + "【PID:" + QString::number(iPid) + "】 CPU使用率 ");
        m_pSTBLOGCpuView->addData(cpu);

        m_pSTBLOGMemView->setTitle(sServerType + "【PID:" + QString::number(iPid) + "】 内存使用率 ");
        m_pSTBLOGMemView->addData(mem);
    }
    else if(!sServerType.compare("tsserver"))
    {
        m_pTSCpuView->setTitle(sServerType + "【PID:" + QString::number(iPid) + "】 CPU使用率 ");
        m_pTSCpuView->addData(cpu);

        m_pTSMemView->setTitle(sServerType + "【PID:" + QString::number(iPid) + "】 内存使用率 ");
        m_pTSMemView->addData(mem);
    }
    else if(!sServerType.compare("updateservice"))
    {
        m_pUPDATECpuView->setTitle(sServerType + "【PID:" + QString::number(iPid) + "】 CPU使用率 ");
        m_pUPDATECpuView->addData(cpu);

        m_pUPDATEMemView->setTitle(sServerType + "【PID:" + QString::number(iPid) + "】 内存使用率 ");
        m_pUPDATEMemView->addData(mem);
    }
    else if(!sServerType.compare("vodserver"))
    {
        m_pVODCpuView->setTitle(sServerType + "【PID:" + QString::number(iPid) + "】 CPU使用率 ");
        m_pVODCpuView->addData(cpu);

        m_pVODMemView->setTitle(sServerType + "【PID:" + QString::number(iPid) + "】 内存使用率 ");
        m_pVODMemView->addData(mem);
    }

}

void MainWindow::updateTestData()
{
    int value=qrand()%100;
    m_pFileSrvCpuView->setTitle("CPU使用率（测试）");
    m_pFileSrvCpuView->addData(value);

    m_pFileSrvMemView->setTitle("内存使用率（测试）");
    m_pFileSrvMemView->addData(value);


    m_pAllMemView->setValue(value);

    m_pAllCpuView->setValue(value);
}

void MainWindow::fileserviceSelect()
{
    setGraphicVisible(false);
    //文件服务
    m_pFileSrvCpuView->setVisible(true);
    m_pFileSrvMemView->setVisible(true);
}

void MainWindow::tsserverSelect()
{
    setGraphicVisible(false);
    //分发服务
    m_pTSCpuView->setVisible(true);
    m_pTSMemView->setVisible(true);
}
void MainWindow::smftpSelect()
{
    setGraphicVisible(false);
    //机顶盒启动服务
    m_pSMFTPCpuView->setVisible(true);
    m_pSMFTPMemView->setVisible(true);
}
void MainWindow::vodserverSelect()
{
    setGraphicVisible(false);
    //视频服务
    m_pVODCpuView->setVisible(true);
    m_pVODMemView->setVisible(true);
}
void MainWindow::updateserviceSelect()
{
    setGraphicVisible(false);

    //升级服务
    m_pUPDATECpuView->setVisible(true);
    m_pUPDATEMemView->setVisible(true);
}
void MainWindow::stblogserviceSelect()
{
    setGraphicVisible(false);
    //机顶盒日志服务
    m_pSTBLOGCpuView->setVisible(true);
    m_pSTBLOGMemView->setVisible(true);
}


void MainWindow::fileserviceHistoryInfo()
{
    //根据用户的选择的时间获取数据库中的内容
    if(!getTimeRange())
    {
        return;
    }

    QVector<QPointF> CPU_data;
    QVector<QPointF> MEM_data;
    m_pDB->getData("fileservice", m_sFromTime, m_sEndTime, CPU_data, MEM_data);
    m_sFromTime = "";
    m_sEndTime = "";
    if(CPU_data.size() < 0 || CPU_data.size() == 0 || MEM_data.size() < 0 || MEM_data.size() == 0)
    {
        QMessageBox::information(this, "提示", "该时间范围内无相关数据！", "确定(&O)");
        return;
    }

    m_pCPUPlotter = new Plotter();

    m_pMEMPlotter = new Plotter();

    //将获取的数据绘制成线条
    m_pCPUPlotter->setCurveData(CPU_data);
    m_pCPUPlotter->setCorrds(100, 0, CPU_data.size(), CPU_data.size()-1);//设置Y轴最大最小值和X轴点数,z是横坐标点数(Y轴最大值，Y轴最小值，X轴点，横坐标点数)
    m_pCPUPlotter->setWindowTitle(QString("从【%1】到【%2】文件服务CPU历史记录").arg(m_sFromTime).arg(m_sEndTime));
    m_pCPUPlotter->showMaximized();

    //将获取的数据绘制成线条
    m_pMEMPlotter->setCurveData(MEM_data);
    m_pMEMPlotter->setCorrds(100, 0, MEM_data.size(), MEM_data.size()-1);//设置Y轴最大最小值和X轴点数,z是横坐标点数(Y轴最大值，Y轴最小值，X轴点，横坐标点数)
    m_pMEMPlotter->setWindowTitle(QString("从【%1】到【%2】文件服务内存历史记录").arg(m_sFromTime).arg(m_sEndTime));
    m_pMEMPlotter->showMaximized();
}

void MainWindow::tsserverHistoryInfo()
{

}
void MainWindow::smftpHistoryInfo()
{

}
void MainWindow::vodserverHistoryInfo()
{

}
void MainWindow::updateserviceHistoryInfo()
{

}
void MainWindow::stblogserviceHistoryInfo()
{

}

void MainWindow::getSearchTime(QString sFromTime, QString sEndTime)
{
    m_sFromTime = sFromTime;
    m_sEndTime = sEndTime;

    qDebug() << "m_sFromTime = "  << m_sFromTime;
    qDebug() << "m_sEndTime = " << m_sEndTime;
}


void MainWindow::setGraphicVisible(bool visible)
{
    //文件服务
    m_pFileSrvCpuView->setVisible(visible);
    m_pFileSrvMemView->setVisible(visible);

    //分发服务
    m_pTSCpuView->setVisible(visible);
    m_pTSMemView->setVisible(visible);

    //机顶盒启动服务
    m_pSMFTPCpuView ->setVisible(visible);
    m_pSMFTPMemView ->setVisible(visible);

    //视频服务
    m_pVODCpuView->setVisible(visible);
    m_pVODMemView->setVisible(visible);

    //升级服务
    m_pUPDATECpuView->setVisible(visible);
    m_pUPDATEMemView->setVisible(visible);

    //机顶盒日志服务
    m_pSTBLOGCpuView->setVisible(visible);
    m_pSTBLOGMemView->setVisible(visible);
}

bool MainWindow::getTimeRange()
{
    //弹出一个时间选择弹出框，然该用户选择需要查看的时间
    TimeSelect *timeRange = new TimeSelect();
    connect(timeRange, SIGNAL(sendTimeToMain(QString,QString)), this, SLOT(getSearchTime(QString, QString)));
    timeRange->exec();
    delete timeRange;

     //用户点击取消按钮
    if(m_sFromTime.isEmpty() || m_sEndTime.isEmpty())
    {
        return false;
    }
    return true;
}

/***********************************************************************
 * 函数名称： getIPFromLogin
 * 函数功能： 从登陆窗口获取IP地址
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月25日10:37:05
 ***********************************************************************/
void MainWindow::getIPFromLogin(QString sLocalIP, QString sServerIP)
{
    //udp监听线程
    m_pListenThread = new CListenThread();
    connect(m_pListenThread, SIGNAL(updateData(QString, QString, int, double, double)),
            this, SLOT(updateData(QString, QString, int, double, double)));
    connect(this, SIGNAL(sendIPToThread(QString, QString)), m_pListenThread, SLOT(getIPFromMainThread(QString, QString)));

    m_sRemoteIP = sServerIP;
    emit sendIPToThread(sLocalIP, sServerIP);
    m_pListenThread->start();
}

/***********************************************************************
 * 函数名称： getIPFromLogin
 * 函数功能： 从登陆窗口获取IP地址
 * 参数说明：
 * 作者 ：    爱在梦幻谷
 * 最后修改：  2013年3月25日10:37:05
 ***********************************************************************/
void MainWindow::closeMainWin()
{
    delete ui;
    this->hide();
    this->close();
}



