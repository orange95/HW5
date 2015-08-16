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
QString remindWhole;
QString remindThing;
QString earlys;

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
        out<<ui->minute->currentItem()->text();
        out<<ui->remindMinute->currentItem()->text();
        out<<ui->textEdit->toPlainText()<<endl;
    }

    QFile file("Calendar.txt");
    if(file.open(QIODevice::ReadOnly)){
        qDebug()<<"opening file";

        QTextStream in(&file);
        while (!in.atEnd()){
            remindWhole = in.readLine();
        }
      }
    else
    {
        qDebug()<<"Fail";
    }

    for(int i=0;i<11;i++)
    {
        remindTime[i]=remindWhole[i];
    }
    earlys[0]=remindWhole[11];
    earlys[1]=remindWhole[12];
    for(int i=13;i<remindWhole.size();i++)
    {
        remindThing[i-11]=remindWhole[i];
    }
    clock->start();
}

void MainWindow::updateTime()
{
    int earlyi=60*earlys.toInt();
    QDateTime datenow;
    QDateTime date;
    datenow = datenow.currentDateTime();
    date = datenow.addSecs(earlyi);
    qDebug()<<earlyi;

    if(date.toString("MM:dd:hh:mm") == remindTime)
    {
        qDebug()<<"yes";
    qDebug()<<date.toString("MM:dd:hh:mm");
    qDebug()<<remindTime;
    ui->reminder->append(remindTime);
    ui->reminder->append(remindThing);
    clock->stop();
    }
    else
    {
        qDebug()<<"No";
    qDebug()<<date.toString("MM:dd:hh:mm");
        qDebug()<<remindTime;
    }
}

