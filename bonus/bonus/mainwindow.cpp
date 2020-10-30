#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstring>
#include "QMessageBox"
#include "Hex.h"
#include <sstream>
#include "rgb.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->first_color->text().length() != 6 || ui->second_color->text().length() != 6) {
        QMessageBox box(this);
        box.setText("Invalid length");
        box.exec();
        return;
    }
    RGB first;
    RGB second;
    try {
        char buf[7];
        strcpy(buf, const_cast<char *>(ui->first_color->text().toStdString().c_str()));
        first = buf;
        strcpy(buf, const_cast<char *>(ui->second_color->text().toStdString().c_str()));
        second = buf;
    }  catch (std::exception &exc) {
        QMessageBox box(this);
        box.setText("Invalid Hex");
        box.exec();
        return;
    }
    RGB result = average(first, second);
    std::stringstream str;
    ui->result_color->setText(QString::fromStdString(trueHex(result, str).str()));
    ui->result_pic->setStyleSheet("background-color: #" + QString::fromStdString(trueHex(result, str).str()));
    ui->first_pic->setStyleSheet("background-color: #" + QString::fromStdString(trueHex(first, str).str()));
    ui->second_pic->setStyleSheet("background-color: #" + QString::fromStdString(trueHex(second, str).str()));
}
