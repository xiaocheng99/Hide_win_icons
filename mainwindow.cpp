#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qsystemtrayicon.h"
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QtDebug>
#include <tchar.h>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


   m_trayicon = new QSystemTrayIcon();


    //设置图标文件，这里先使用路径来设置，后面介绍使用qt资源文件设置图标文件
    //我将图标放在了项目路径下，并使用了绝对路径
    m_trayicon->setIcon(QIcon(":/new/prefix1/icon.png"));

    m_trayicon->setToolTip("程序作者：小成\n 连续右击两次课影藏/显示桌面图标");


    //显示托盘图标
    m_trayicon->show();
    connect(m_trayicon, &QSystemTrayIcon::activated, this, &MainWindow::activeTray);//点击托盘，执行相应的动作
    //添加菜单
    m_menu = new QMenu(this);
    QAction *m_action1 = new QAction(m_menu);
    m_action1->setText("退出程序");
    m_menu->addAction(m_action1);
    m_trayicon->setContextMenu(m_menu);

    connect(m_action1, &QAction::triggered, this, &MainWindow::exitApp);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::activeTray(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Context:
        showMenu();
        break;
    case QSystemTrayIcon::DoubleClick:
        //showWindow();
        break;
    case QSystemTrayIcon::Trigger:
        //showMessage();
        break;
    }
}

void MainWindow::showMenu()
{
    m_menu->show();
    qDebug()<<"menu";
}
int MainWindow::exitApp()
{
    qDebug()<<"exit";
//     QApplication::exit(0);

//this->close();
//     qApp->quit();
    qApp->exit(0);
//     m_trayicon->hide();
emit exit();

    return 0 ;


}

void MainWindow::on_pushButton_clicked()
{
    qApp->exit(0);
}

    void MainWindow::gethook(HOOKPROC LowLevelMouseProc)
    {
        MSG msg;


        SetWindowsHookExW(WH_MOUSE_LL, LowLevelMouseProc, GetModuleHandleW(0), 0);
        while (GetMessageW(&msg, 0, 0, 0))DispatchMessageW(&msg);
    }

