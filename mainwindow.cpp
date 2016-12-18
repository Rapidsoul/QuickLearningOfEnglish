#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::showMaximized();
    db = new DbManager("D:\\Work\\Qt project\\QuickLearningOfEnglish\\res\\db\\dictionary.sqlite", this);
    setRandomQuestion();
}

MainWindow::~MainWindow()
{
    delete db;
    delete ui;
}

void MainWindow::setRandomQuestion()
{
    QVector<QString> randomRecord = db->getRandomRecord();
    if (randomRecord[0] != 0) {
        ui->lineEdit_answer->setText("");
        QString question = randomRecord[0];
        question[0] = question[0].toUpper();
        ui->label_wordToTranslate->setText(question);
        ui->label_image->setPixmap(QPixmap(randomRecord[1]));
        qDebug() << randomRecord[1];
    }
}

void MainWindow::on_pushButton_check_clicked()
{
    QString question = ui->label_wordToTranslate->text();
    QString answer = ui->lineEdit_answer->text();
    question = question.toLower(); answer = answer.toLower();
    if (db->checkAnswer(question, answer))
    {
        setRandomQuestion();
    }
}

void MainWindow::on_pushButton_skip_clicked()
{
    setRandomQuestion();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About Quick Learning of English", "Author: Serhii Yakubovych\nVersion: 0.001a");
}
