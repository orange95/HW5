#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include "QString"
#include "QDebug"
#include "QFileDialog"
#include "QTime"
#include "QTimer"
#include "QDateTime"
#include "QVector"
#include "QList"

QString remindTime;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    clock = new QTimer;
    clock ->setInterval(1000);
    connect(clock,SIGNAL(timeout()),this,SLOT(updateTime()));

    codec = QTextCodec::codecForName("Big5");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString whenSaved="Saved at ";
    QDateTime time;
    time = time.currentDateTime();
    whenSaved.append(time.toString("hh:mm:ss"));
    ui->show->append(whenSaved);

    QFile filewrite("Calendar.txt");
    if(filewrite.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
    {
        QTextStream out (&filewrite);
        out<<ui->month->currentItem()->text();
        out<<":";
        out<<ui->day1->currentItem()->text();
        out<<ui->day2->currentItem()->text();
        out<<":";
        out<<ui->hour1->currentItem()->text();
        out<<ui->hour2->currentItem()->text();
        out<<":";
        out<<ui->minute->currentItem()->text()<<endl;
//        out<<ui->remindMinute->currentItem()->text()<<endl;
//        out<<ui->textEdit->toPlainText()<<endl;
    }

    QFile file("Calendar.txt");
    if(file.open(QIODevice::ReadOnly)){
        qDebug()<<"opening file";

        QTextStream in(&file);
        while (!in.atEnd()){
            remindTime = in.readLine();
        }
      }
    else
    {
        qDebug()<<"Fail";
    }

    clock->start();
}


void MainWindow::updateTime()
{
    QDateTime date;
    date = date.currentDateTime();

    if(date.toString("MM:dd:hh:mm") == remindTime)
    {
        qDebug()<<"yes";
    qDebug()<<date.toString("MM:dd:hh:mm");
    qDebug()<<remindTime;}
    else
    {
        qDebug()<<"No";
    qDebug()<<date.toString("MM:dd:hh:mm");
        qDebug()<<remindTime;
    }
}

