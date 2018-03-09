/*
* Markdown Organizer
* Copyright (C) 2016-2018 ThoughtLogix
* 
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QFile>
#include <QString>
#include <QTextStream>

#ifndef LOGMANAGER_H
#define LOGMANAGER_H

class LogManager : public QObject
{
    Q_OBJECT

public:
    LogManager(QObject *parent = nullptr);
    ~LogManager();
    static LogManager *instance();

    void fatal(const QString str);
    void error(const QString str);
    void warning(const QString str);
    void debug(const QString str);
    void info(const QString str);

signals:
    void messageLogged(const QString msg);

private:
    static LogManager *logManager;
    QString formatLogMsg(QString type, QString date, QString msg);
    QFile *logFile;
    QTextStream *logStream;
};

#define LOG_MANAGER LogManager::instance()
#define LOG_MANAGER_INITIALIZE LogManager::instance()
#define LOG_FATAL(msg) LogManager::instance()->fatal(msg)
#define LOG_ERROR(msg) LogManager::instance()->error(msg)
#define LOG_WARNING(msg) LogManager::instance()->warning(msg)
#define LOG_DEBUG(msg) LogManager::instance()->debug(msg)
#define LOG_INFO(msg) LogManager::instance()->info(msg)

#endif // LOGMANAGER_H
