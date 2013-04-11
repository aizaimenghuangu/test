#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QtNetwork/QUdpSocket>

const quint16 LOGIN_LISTEN_PORT = 6667;
const quint16 LOGIN_SEND_PORT = 6668;

const quint16 TEST_TIMEOUT = 3000;


class QHostAddress;
class QLineEdit;
class QAbstractButton;
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private:
    Ui::login *ui;
    void initData();
    QHostAddress getLocalIPAddress();
    void setIP4Validator(QLineEdit *lineEdit);
    bool listen();
    bool PingAClient(QString clientip);
    void SpilitStr(QString sourcestr,QString SeperatorChar,QStringList &ResultTS);

    QUdpSocket *m_pTestLinkSocket;
    bool m_bLinkOk;
    QTimer *m_pTestLinkTimer;

signals:
    void sendIPToMain(QString sLocalIP, QString sRemoteIP);
    void cancelBtnClick();
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_linkTestBtn_clicked();
    void processPendingDatagrams();
    void testLinkTimerOut();
};

#endif // LOGIN_H
