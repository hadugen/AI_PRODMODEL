#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QList>
#include <QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void refreshRules();
    ~MainWindow();

private slots:
    void on_button_addRule_clicked();

    void on_button_ask_clicked();

private:
    Ui::MainWindow *ui;
    QFile* fileDesc;
    QList <QString> ifConditions, thenConditions;
    QMessageBox *msg;
    QString question;
};

#endif // MAINWINDOW_H
