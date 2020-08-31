#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qsystemtrayicon.h"
#include "qsystemtrayicon.h"
#include <tchar.h>
#include <windows.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSystemTrayIcon *m_trayicon;
  QMenu * m_menu ;



    void activeTray(QSystemTrayIcon::ActivationReason reason);
    void showMenu();
    int exitApp();

    void gethook(HOOKPROC LowLevelMouseProc);
 signals:
    void exit();
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
