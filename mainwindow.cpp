#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileDesc = new QFile("rules.txt");
    ui->tableWidget_rules->setColumnCount(2);
    QString headers = "ЕСЛИ ТО";
    ui->tableWidget_rules->setHorizontalHeaderLabels(headers.split(" "));
    refreshRules();
    msg = new QMessageBox(this);
}

MainWindow::~MainWindow()
{
    delete fileDesc;
    delete ui;
}

void MainWindow::on_button_addRule_clicked()
{
    if(ui->lineEdit_if->text().size() == 0 || ui->lineEdit_then->text().size() == 0)
        return;
    if(!fileDesc->open(QIODevice::WriteOnly |
                       QIODevice::Append |
                       QIODevice::Text |
                       QIODevice::Unbuffered))
        qDebug() << "error";

    QTextStream fileStream(fileDesc);
    fileStream << (QString)"ЕСЛИ " << ui->lineEdit_if->text() << (QString)" ТО " << ui->lineEdit_then->text() << endl;
    ui->lineEdit_if->clear();
    ui->lineEdit_then->clear();
    fileDesc->close();
    refreshRules();
}

void MainWindow::refreshRules()
{
    if(!fileDesc->open(QIODevice::ReadOnly |
                       QIODevice::Text))
        qDebug() << "error";

    ifConditions.clear();
    thenConditions.clear();

    QTextStream fileStream(fileDesc);
    QVector <QString> rules;
    while(!fileStream.atEnd())
    {
        rules.push_back(fileStream.readLine());
    }
    fileDesc->close();
    ui->tableWidget_rules->setRowCount(rules.size());
    QStringList temp;
    QString cond;
    for(int i = 0; i < rules.size(); i++)
    {
        temp = rules.at(i).split("ТО");
        cond = temp.at(0).mid(4);
        cond = cond.trimmed();
        QTableWidgetItem* item = new QTableWidgetItem(cond);
        ifConditions.push_back(cond);
        ui->tableWidget_rules->setItem(i,0,item);
        cond = temp.at(1);
        cond = cond.trimmed();
        item = new QTableWidgetItem(cond);
        thenConditions.push_back(cond);
        ui->tableWidget_rules->setItem(i,1,item);
    }
}

void MainWindow::on_button_ask_clicked()
{
    this->question = ui->lineEdit_question->text();
    refreshRules();
    QString question = ui->lineEdit_question->text();

    for(int i = 0; i < ifConditions.size(); i++)
    {
        if(ifConditions.at(i).compare(question) == 0)
        {
            question = thenConditions.at(i).trimmed();
            i = 0;
        }
    }
    if(this->question.compare(question) != 0 )
    {
        msg->setText(question);
    }
    else
    {
        msg->setText("Интересующий вас вопрос отсутсвует в базе знаний");
    }
    msg->show();
}
