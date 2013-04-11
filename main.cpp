#include <QtGui/QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QDesktopWidget>
#include <QStyleFactory>
#include <QStyle>
#include "mainwindow.h"
#include <QDebug>

static void setTextCodec()
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
}

int waitForTray();
void sendMsg();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setTextCodec();
    QTranslator qtTranslator;
#ifdef WIN32
    qtTranslator.load("D:\\Users\\CC\\AppData\\qt_zh_CN.qm");
#else
    qtTranslator.load("/evideoktv/bin/qt_zh_CN.qm");
#endif
    app.installTranslator(&qtTranslator);

    //窗体居中显示
    QDesktopWidget *desktop=QApplication::desktop();
    int width=desktop->width();
    int height=desktop->height();

    MainWindow w;
    w.setWindowTitle("X86锋云测试工具--CPU内存查看器");
    //设置窗口没有最大化按钮
    w.setWindowFlags(Qt::WindowMinimizeButtonHint);
//    w.move((width-w.width())/2,(height-w.height())/2);
    w.move(300, 100);
//    w.setFixedSize(w.width() + 100, w.height() + 300);
    w.show();
    //应用样式
    QApplication::setStyle(QStyleFactory::create("cleanlooks"));
    QApplication::setPalette(QApplication::style()->standardPalette());

    w.show();

    return app.exec();
}
