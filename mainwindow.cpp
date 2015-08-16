#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include "QTime"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    codec = QTextCodec::codecForName("Big5");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString whenSaved="Saved at ";
    QTime time;
    time = time.currentTime();
    whenSaved.append(time.toString("hh:mm"));
    //qDebug() << time.toString("hh:mm");
    ui->show->append(whenSaved);
}
