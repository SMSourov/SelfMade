#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

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
    QString line1 = ui->lineEdit->text();
    QString line2 = ui->lineEdit_2->text();
    QString line3 = ui->lineEdit_3->text();

    QString answer, tempLine1, tempLine2;
    QString carry = "0", zero = "0", one = "1";
    int bitSize = line3.toUInt();

    while (line1.size() < bitSize)
    {
        line1.insert(0, "0");
    }

    while (line2.size() < bitSize)
    {
        line2.insert(0, "0");
    }

    for (int start = bitSize - 1; start >= 1; start--)
    {
        tempLine1 = line1[start];
        if (tempLine1.compare(zero) == 0)
        {
            tempLine2 = line2[start];
            if (tempLine2.compare(zero) == 0)
            {
                if (carry.compare(zero) == 0)
                {
                    // c = 0, f = 0, s = 0; a = 0, c = 0
                    answer.insert(0, zero);
                    // This part is OK
                }
                else
                {
                    // c = 1, f = 0, s = 0, a = 1, c = 1
                    answer.insert(0, one);
                    // This part is OK
                }
            }
            else
            {
                if (carry.compare(zero) == 0)
                {
                    // c = 0, f = 0, s = 1; a = 1, c = 1
                    answer.insert(0, one);
                    carry = one;
                    // This part is OK
                }
                else
                {
                    // c = 1, f = 0, s = 1; a = 0, c = 1
                    answer.insert(0, zero);
                    // This part is OK
                }
            }
        }
        else
        {
            tempLine2 = line2[start];
            if (tempLine2.compare(zero) == 0)
            {
                if (carry.compare(zero) == 0)
                {
                    // c = 0, f = 1, s = 0; a = 1, c = 0
                    answer.insert(0, one);
                    // This part is OK
                }
                else
                {
                    // c = 1, f = 1, s = 0; a = 0, c = 0
                    answer.insert(0, zero);
                    carry = zero;
                    // This part is OK
                }
            }
            else
            {
                if (carry.compare(zero) == 0)
                {
                    // c = 0, f = 1, s = 1; a = 0, c = 0
                    answer.insert(0, zero);
                    // This part is OK
                }
                else
                {
                    // c = 1, f = 1, s = 1; a = 1, c = 1
                    answer.insert(0, one);
                    carry = one;
                    // This part is OK
                }
            }
        }
    }

    // Not sure whether this part is OK or not
    if (carry.compare(zero) == 0)
    {
        answer.insert(0, zero);
    }
    else
    {
        answer.insert(0, one);
    }

    // Change the font size of the pop up menu
    answer.insert(0, "<font size = 6>");
    answer.insert(answer.size(), "</font>");

    // Making the text of the message box selectable
    // This effects the full application
    qApp->setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; }");
    QMessageBox message;
    message.setTextInteractionFlags(Qt::TextSelectableByMouse);
    message.information(this, "Answer", answer);
}

