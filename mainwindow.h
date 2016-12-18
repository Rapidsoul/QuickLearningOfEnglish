#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setRandomQuestion();

private slots:
    void on_pushButton_check_clicked();
    void on_pushButton_skip_clicked();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    DbManager *db;
};

#endif // MAINWINDOW_H
