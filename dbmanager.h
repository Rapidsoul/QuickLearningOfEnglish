#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>

class DbManager
{
public:
    DbManager(const QString& path, QMainWindow *parent_win);
    void getAllWords();
    bool checkAnswer(const QString &question, const QString& answer);
    QVector<QString> getRandomRecord();
private:
    QSqlDatabase m_db;
    QMainWindow *win;
};

#endif // DBMANAGER_H
