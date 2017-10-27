#include "mainwindow.h"
#include <ui_mainwindow.h>
#include "cameracontrolshelp.h"
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mygl->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionImport_triggered() {
    QString filename = QFileDialog::getOpenFileName(0, QString("Load OBJ File"), QDir::currentPath().append(QString("../..")), QString("*.obj"));
    ui->mygl->importToMesh(filename);
}

void MainWindow::on_actionExport_triggered()
{
    QString filename = QFileDialog::getSaveFileName(0, QString("Save Image"), QString("../.."), QString("*.obj"));
    QString ext = filename.right(4);
    if(QString::compare(ext, QString(".obj")) != 0)
    {
        filename.append(QString(".obj"));
    }
    ui->mygl->exportMeshToObj(filename);
    //QImageWriter writer(filename);
    //writer.setFormat("bmp");
    //if(!writer.write(rendered_image))
    //{
    //    qDebug() << writer.errorString();
    //}
}

void MainWindow::on_actionCamera_Controls_triggered()
{
    CameraControlsHelp* c = new CameraControlsHelp();
    c->show();
}
