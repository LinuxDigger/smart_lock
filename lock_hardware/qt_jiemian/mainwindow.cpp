#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QTimer>
#include <QDateTime>
#include <QFile>
#include <QDebug>
#include <QKeyEvent>
#include <QString>
#include <QPixmap>
#include <unistd.h>
#include <src/camera/camera.h>
#include <src/server_moto/server_moto.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timerUpdate();

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

//    file_name = "./file.txt";
//    file_read();

    m_fileSystemWatcher = new QFileSystemWatcher(this);
    m_fileSystemWatcher->addPath(file_name);
    connect(m_fileSystemWatcher, SIGNAL(fileChanged(QString)), this, SLOT(fileChanged(QString)));

    ui->Tips_label_1->setText("\r\nPress * to unlock");
    ui->stackedWidget->setCurrentWidget(ui->page);

    this->showFullScreen();

    printf("\r\nserver_moto_init() = %d\r\n", server_moto_init());

    CLOSE_DOOR();
    LOCK_DOOR();
}

MainWindow::~MainWindow()
{    
    delete ui;

    CLOSE_DOOR();
    sleep(2);
    LOCK_DOOR();
    server_moto_exit();
}

//void MainWindow::file_read(void)
//{

//    ui->label_4->setText("xxxx");
//    ui->label_6->setText("xxxx");
//    QFile file(file_name);
//    if (file.exists()) {
//        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//            return;
//        }
//        while (!file.atEnd()) {
//            QString line = file.readLine();
//            if (line.startsWith("ID:")) {
//                QString str = line.section(':', 1).trimmed();
//                if (str.isEmpty()) {
//                    str = "xxxx";
//                }
//                ui->label_4->setText(str);
//            } else if (line.startsWith("password:")) {
//                QString str = line.section(':', 1).trimmed();
//                if (str.isEmpty()) {
//                    str = "xxxx";
//                }
//                ui->label_6->setText(str);
//            }
//        }
//        file.close();
//    }
//}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (mode == 0)
    {
        if (event->key() == Qt::Key_Backspace)
        {
            if (unlock_state == 0)
            {
                ui->Tips_label_1->setText("\r\nPress again");
                unlock_state = 1;
            }
            else if (unlock_state == 1)
            {
//                ui->password_lcd->hide();
                ui->Tips_label_2->setText("Please input password");
                ui->Tips_label_3->setText("press # to confirm your password\r\nPress * to backspace");
                ui->stackedWidget->setCurrentWidget(ui->page_2);

                mode = 1;
                input_password = "";
            }
        }
        else
        {
            ui->Tips_label_1->setText("\r\nPress * to unlock");
            unlock_state = 0;
        }
    }

    if (mode == 1)
    {
        if (input_password.size() < 10)
        {
            if (event->key() == Qt::Key_0)
            {
                input_password += "0";
            }

            if (event->key() == Qt::Key_1)
            {
                input_password += "1";
            }

            if (event->key() == Qt::Key_2)
            {
                input_password += "2";
            }

            if (event->key() == Qt::Key_3)
            {
                input_password += "3";
            }

            if (event->key() == Qt::Key_4)
            {
                input_password += "4";
//                server_moto_config(-1, 0);
            }

            if (event->key() == Qt::Key_5)
            {
                input_password += "5";
            }

            if (event->key() == Qt::Key_6)
            {
                input_password += "6";
//                server_moto_config(-1, 270);
            }

            if (event->key() == Qt::Key_7)
            {
                input_password += "7";
//                server_moto_config(0, -1);
            }

            if (event->key() == Qt::Key_8)
            {
                input_password += "8";
            }

            if (event->key() == Qt::Key_9)
            {
                input_password += "9";
//                server_moto_config(180, -1);
            }
        }

        if (event->key() == Qt::Key_Backspace)
        {
            input_password = input_password.left(input_password.size() - 1);
        }

        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        {
            if (input_password == "886")
            {
                this->close();
            }

            if (input_password == "7182934650")
            {
                if (take_a_picture() == 0)
                {
                    ui->stackedWidget->setCurrentWidget(ui->page_4);
                    ui->jpg_label->setPixmap(QPixmap("/capture.jpg"));

                    mode = 4;
                }
            }

            if (input_password == "980665")
            {
                sleep(2);
                UNLOCK_DOOR();
                OPEN_DOOR();
            }

            input_password = "";
//            mode = 3; /* 进入验证密码环节 */
        }

        ui->password_lcd->display(input_password);
    }

    if (mode == 4)
    {
        if (event->key() == Qt::Key_Backspace)
        {
            ui->stackedWidget->setCurrentWidget(ui->page_2);

            mode = 2;
        }
    }
}

void MainWindow::into_input(void)
{
    return;
}

void MainWindow::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy/M/d dddd \n hh:mm:ss");
    ui->Time_label_1->setText(str);
    str = time.toString("yyyy/M/d hh:mm");
    ui->Time_label_2->setText(str);
}

//void MainWindow::fileChanged(QString str)
//{
//    qDebug() << str;
//    file_read();
//}
