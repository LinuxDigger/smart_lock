
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemWatcher>
#include <src/camera/camera.h>
#include <src/server_moto/server_moto.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void into_input(void);
    void keyPressEvent(QKeyEvent *event);

public slots:
    void timerUpdate(void);
private slots:

private:
    Ui::MainWindow *ui;
    QString strContent;
    QFileSystemWatcher *m_fileSystemWatcher;
    QString file_name;
    unsigned char unlock_state = 0;
    unsigned char mode = 0;
    QString input_password = "";
};

#endif // MAINWINDOW_H
