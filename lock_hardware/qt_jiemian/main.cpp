#include "mainwindow.h"
#include <QApplication>
#include <thread>
#include <src/server_moto/server_moto.h>
#include "lock.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	std::thread *task = new std::thread(lock_main);

    return a.exec();
}
