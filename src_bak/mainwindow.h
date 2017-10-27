#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    void on_actionImport_triggered();
    void on_actionExport_triggered();
    void on_actionCamera_Controls_triggered();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
