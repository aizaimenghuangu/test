#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

class login;
class myChart1;
class myGauge1;
class myGauge2;
class CListenThread;
class QPushButton;
class QLabel;
class QMenu;
class QHBoxLayout;
class DatabaseManager;
class Plotter;
class InsertThread;
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    //数据库管理
    DatabaseManager *m_pDB;

    //绘图
    Plotter *m_pCPUPlotter;
    Plotter *m_pMEMPlotter;

    //数据插入线程
    InsertThread *m_pInsertThread;

    //文件服务
    myChart1 *m_pFileSrvCpuView;
    myChart1 *m_pFileSrvMemView;

    //分发服务
    myChart1 *m_pTSCpuView;
    myChart1 *m_pTSMemView;

    //机顶盒启动服务
    myChart1 *m_pSMFTPCpuView;
    myChart1 *m_pSMFTPMemView;

    //视频服务
    myChart1 *m_pVODCpuView;
    myChart1 *m_pVODMemView;

    //升级服务
    myChart1 *m_pUPDATECpuView;
    myChart1 *m_pUPDATEMemView;

    //机顶盒日志服务
    myChart1 *m_pSTBLOGCpuView;
    myChart1 *m_pSTBLOGMemView;

    myGauge1 *m_pAllMemView;
    myGauge2 *m_pAllCpuView;
    login *m_pLogin;
    CListenThread *m_pListenThread;

    QPushButton *m_pTypeSelectBtn;
    QPushButton *m_pHistoryInfoBtn;
    QLabel *m_pAllMemViewLabel;
    QLabel *m_pAllCpuViewLabel;
    QMenu *m_pTypeSelectMenu;
    QMenu *m_pHistoryInfoMenu;

    QString m_sRemoteIP;
    QString m_sFromTime;
    QString m_sEndTime;

    void initUI();
    void initDB();
    void setGraphicVisible(bool);
    bool getTimeRange();
private slots:
    void getIPFromLogin(QString sLocalIP, QString sServerIP);
    void closeMainWin();

    void updateData(QString sServerType, QString sUser, int iPid, double cpu, double mem);
    void updateTestData();

    void fileserviceSelect();
    void tsserverSelect();
    void smftpSelect();
    void vodserverSelect();
    void updateserviceSelect();
    void stblogserviceSelect();

    //历史记录查看器
    void fileserviceHistoryInfo();
    void tsserverHistoryInfo();
    void smftpHistoryInfo();
    void vodserverHistoryInfo();
    void updateserviceHistoryInfo();
    void stblogserviceHistoryInfo();

    void getSearchTime(QString sFromTime, QString sEndTime);

signals:
    void sendIPToThread(QString, QString);
    void sendInsertData(DatabaseManager*, QString sRemoteIP, QString sServerType, QString sDateTime, double mem, double cpu);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
