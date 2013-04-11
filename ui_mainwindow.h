/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Apr 10 17:40:12 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_help;
    QAction *action_about;
    QAction *action_setup;
    QAction *action_quit;
    QAction *action_DBSetup;
    QAction *action_getKMNewsongList;
    QAction *action_getNewSongList;
    QAction *action_getPollingSongList;
    QAction *action_getVipList;
    QAction *action_getSongInfoList;
    QAction *action_getSongFileList;
    QAction *action_testNewsongList;
    QAction *action_runAutoTest;
    QWidget *centralWidget;
    QTableView *tableView;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *setupMenu;
    QMenu *aboutMenu;
    QMenu *queryMenu;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(610, 474);
        action_help = new QAction(MainWindow);
        action_help->setObjectName(QString::fromUtf8("action_help"));
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QString::fromUtf8("action_about"));
        action_setup = new QAction(MainWindow);
        action_setup->setObjectName(QString::fromUtf8("action_setup"));
        action_quit = new QAction(MainWindow);
        action_quit->setObjectName(QString::fromUtf8("action_quit"));
        action_quit->setSoftKeyRole(QAction::NoSoftKey);
        action_DBSetup = new QAction(MainWindow);
        action_DBSetup->setObjectName(QString::fromUtf8("action_DBSetup"));
        action_getKMNewsongList = new QAction(MainWindow);
        action_getKMNewsongList->setObjectName(QString::fromUtf8("action_getKMNewsongList"));
        action_getNewSongList = new QAction(MainWindow);
        action_getNewSongList->setObjectName(QString::fromUtf8("action_getNewSongList"));
        action_getPollingSongList = new QAction(MainWindow);
        action_getPollingSongList->setObjectName(QString::fromUtf8("action_getPollingSongList"));
        action_getVipList = new QAction(MainWindow);
        action_getVipList->setObjectName(QString::fromUtf8("action_getVipList"));
        action_getSongInfoList = new QAction(MainWindow);
        action_getSongInfoList->setObjectName(QString::fromUtf8("action_getSongInfoList"));
        action_getSongFileList = new QAction(MainWindow);
        action_getSongFileList->setObjectName(QString::fromUtf8("action_getSongFileList"));
        action_testNewsongList = new QAction(MainWindow);
        action_testNewsongList->setObjectName(QString::fromUtf8("action_testNewsongList"));
        action_runAutoTest = new QAction(MainWindow);
        action_runAutoTest->setObjectName(QString::fromUtf8("action_runAutoTest"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(0, 0, 611, 411));
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 610, 23));
        fileMenu = new QMenu(menuBar);
        fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
        setupMenu = new QMenu(menuBar);
        setupMenu->setObjectName(QString::fromUtf8("setupMenu"));
        aboutMenu = new QMenu(menuBar);
        aboutMenu->setObjectName(QString::fromUtf8("aboutMenu"));
        queryMenu = new QMenu(menuBar);
        queryMenu->setObjectName(QString::fromUtf8("queryMenu"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(fileMenu->menuAction());
        menuBar->addAction(setupMenu->menuAction());
        menuBar->addAction(queryMenu->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(aboutMenu->menuAction());
        fileMenu->addAction(action_quit);
        setupMenu->addAction(action_DBSetup);
        aboutMenu->addAction(action_help);
        aboutMenu->addAction(action_about);
        queryMenu->addAction(action_getKMNewsongList);
        queryMenu->addAction(action_getNewSongList);
        queryMenu->addAction(action_getPollingSongList);
        queryMenu->addAction(action_getVipList);
        queryMenu->addAction(action_getSongInfoList);
        queryMenu->addAction(action_getSongFileList);
        menu->addAction(action_runAutoTest);
        mainToolBar->addAction(action_runAutoTest);
        mainToolBar->addAction(action_getKMNewsongList);
        mainToolBar->addAction(action_getNewSongList);
        mainToolBar->addAction(action_getPollingSongList);
        mainToolBar->addAction(action_getVipList);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_getSongInfoList);
        mainToolBar->addAction(action_getSongFileList);
        mainToolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_help->setText(QApplication::translate("MainWindow", "\345\270\256\345\212\251", 0, QApplication::UnicodeUTF8));
        action_about->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216\350\275\257\344\273\266", 0, QApplication::UnicodeUTF8));
        action_setup->setText(QApplication::translate("MainWindow", "\347\263\273\347\273\237\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        action_quit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        action_quit->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", 0, QApplication::UnicodeUTF8));
        action_DBSetup->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\345\272\223\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        action_getKMNewsongList->setText(QApplication::translate("MainWindow", "K\347\261\263\346\226\260\346\255\214\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        action_getNewSongList->setText(QApplication::translate("MainWindow", "\346\226\260\346\255\214\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        action_getPollingSongList->setText(QApplication::translate("MainWindow", "\345\205\254\346\222\255\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        action_getVipList->setText(QApplication::translate("MainWindow", "VIP\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        action_getSongInfoList->setText(QApplication::translate("MainWindow", "\346\255\214\346\233\262\344\277\241\346\201\257\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        action_getSongFileList->setText(QApplication::translate("MainWindow", "\346\255\214\346\233\262\346\226\207\344\273\266\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        action_testNewsongList->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\346\226\260\346\255\214\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        action_runAutoTest->setText(QApplication::translate("MainWindow", "\350\277\220\350\241\214\350\207\252\345\212\250\345\214\226\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        action_runAutoTest->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0, QApplication::UnicodeUTF8));
        fileMenu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        setupMenu->setTitle(QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        aboutMenu->setTitle(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0, QApplication::UnicodeUTF8));
        queryMenu->setTitle(QApplication::translate("MainWindow", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
