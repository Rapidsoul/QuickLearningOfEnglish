#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>

DbManager::DbManager(const QString& path, QMainWindow *parent_win)
{
   win = parent_win;
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName(path);

   if (!m_db.open())
   {
      qDebug() << "Error: connection with database fail";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}

void DbManager::getAllWords() {
    QSqlQuery query = QSqlQuery(m_db);
    if (!query.exec("SELECT * FROM eng_ukr")) {
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
        return;
    }
    while (query.next()) {
        qDebug() << query.record();
    }
}

bool DbManager::checkAnswer(const QString &question, const QString &answer) {
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database fail";
       return false;
    }
    QSqlQuery query;
    if (query.exec("SELECT eng, ukr FROM eng_ukr WHERE eng=\'"+question+"\' AND ukr=\'"+answer+"\'")) {
        if (query.next()) {
            QString message = "English word = " + query.value(0).toString() + "\n" +
                    "Ukrainian translate = " + query.value(1).toString();
            QMessageBox::information(win, "Successful answer!", message);
            return true;
        } else {
            QMessageBox::warning(win, "Fail!", "Fail answer, please try again.");
            return false;
        }
    }
    else
        return false;
}

QVector<QString> DbManager::getRandomRecord() {
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    QSqlQuery query;
    int dictionary_size = 0;
    if (query.exec("SELECT COUNT(*) FROM eng_ukr")) {
        if (query.next()) {
            dictionary_size = query.value(0).toInt(0);
        }
        else return {0};
    }
    else return {0};
    QString random_el = QString::number(rand()%(dictionary_size-1)+1);
    if (query.exec("SELECT eng, ukr, img FROM eng_ukr WHERE word_id=\'" + random_el + "\'")) {
        if (query.next()) {
            QVector<QString> record = {query.value(0).toString(),
                                       query.value(2).toString()};
            return record;
        } else {
            QMessageBox::warning(win, "Error!", query.lastError().databaseText()+"\n"
                                 +query.lastError().driverText());
        }
    }
    return {0};
}
